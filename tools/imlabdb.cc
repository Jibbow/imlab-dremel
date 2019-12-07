// ---------------------------------------------------------------------------
// IMLAB
// ---------------------------------------------------------------------------
#include <dlfcn.h>
#include <chrono>  // NOLINT
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "database.h"
#include "imlab/schemac/schema_parse_context.h"
#include "imlab/queryc/query_parse_context.h"
#include "imlab/queryc/query_compiler.h"
// ---------------------------------------------------------------------------
using SchemaParseContext = imlab::schemac::SchemaParseContext;
using QueryParseContext = imlab::queryc::QueryParseContext;
using QueryCompiler = imlab::queryc::QueryCompiler;
// ---------------------------------------------------------------------------

imlab::Database loadDatabase() {
    imlab::Database database{};

    std::fstream warehouse_file("../data/tpcc_5w/tpcc_warehouse.tbl", std::fstream::in);
    database.LoadWarehouse(warehouse_file);
    std::fstream district_file("../data/tpcc_5w/tpcc_district.tbl", std::fstream::in);
    database.LoadDistrict(district_file);
    std::fstream customer_file("../data/tpcc_5w/tpcc_customer.tbl", std::fstream::in);
    database.LoadCustomer(customer_file);
    std::fstream history_file("../data/tpcc_5w/tpcc_history.tbl", std::fstream::in);
    database.LoadHistory(history_file);
    std::fstream neworder_file("../data/tpcc_5w/tpcc_neworder.tbl", std::fstream::in);
    database.LoadNewOrder(neworder_file);
    std::fstream order_file("../data/tpcc_5w/tpcc_order.tbl", std::fstream::in);
    database.LoadOrder(order_file);
    std::fstream orderline_file("../data/tpcc_5w/tpcc_orderline.tbl", std::fstream::in);
    database.LoadOrderLine(orderline_file);
    std::fstream item_file("../data/tpcc_5w/tpcc_item.tbl", std::fstream::in);
    database.LoadItem(item_file);
    std::fstream stock_file("../data/tpcc_5w/tpcc_stock.tbl", std::fstream::in);
    database.LoadStock(stock_file);

    return database;
}

void ExecuteQuery(imlab::Database &db, const std::string &dylib_path) {
    void *handle = dlopen(dylib_path.c_str(), RTLD_NOW);
    if (!handle) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(1);
    }
    auto run_query = reinterpret_cast<void (*)(imlab::Database &)>(dlsym(handle, "Run"));
    if (!run_query) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(1);
    }

    run_query(db);

    if (dlclose(handle)) {
        std::cerr << "error: " << dlerror() << std::endl;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    // Load schema and database content

    auto load_schema_begin = std::chrono::steady_clock::now();
    std::cout << "Loading schema information..." << std::flush;
    std::ifstream schema_file("../data/schema.sql");
    SchemaParseContext schema_parse_context;
    auto schema = schema_parse_context.Parse(schema_file);
    auto load_schema_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - load_schema_begin).count();
    std::cout << " [done in " << load_schema_duration << " ms]" << std::endl;

    auto load_db_begin = std::chrono::steady_clock::now();
    std::cout << "Loading database..." << std::flush;
    auto db = loadDatabase();
    auto load_db_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now() - load_db_begin).count();
    std::cout << " [done in " << load_db_duration << " ms]" << std::endl;

    // Prepare sql query parser
    QueryParseContext query_parse_context {schema};

    // Starting REPL
    std::cout << "Starting SQL interpreter - close with Ctrl+D" << std::endl;
    std::cout << "To enable statistics, enter \"enable_stats\"" << std::endl;
    std::cout << ">>> " << std::flush;
    bool enable_stats = false;
    std::string line{};
    while (std::getline(std::cin, line)) {
        if (line == "enable_stats") {
            enable_stats = true;
        } else {
            try {
                //---------------------------------------------------------------------------------------
                auto parse_query_begin = std::chrono::steady_clock::now();

                std::istringstream in_stream(line);
                auto &query = query_parse_context.Parse(in_stream);

                auto parse_query_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - parse_query_begin).count();
                //---------------------------------------------------------------------------------------

                //---------------------------------------------------------------------------------------
                auto code_generation_begin = std::chrono::steady_clock::now();

                std::ofstream query_out_h("../tools/queryc/gen/query.h", std::ofstream::trunc);
                std::ofstream query_out_cc("../tools/queryc/gen/query.cc", std::ofstream::trunc);
                QueryCompiler compiler {query_out_h, query_out_cc};

                compiler.Compile(query);

                query_out_h.close();
                query_out_cc.close();

                auto code_generation_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - code_generation_begin).count();
                //---------------------------------------------------------------------------------------

                //---------------------------------------------------------------------------------------
                auto code_compilation_begin = std::chrono::steady_clock::now();

                auto err = system("c++ ../tools/queryc/gen/query.cc -o ../tools/queryc/gen/query.so -std=c++17 -shared -fPIC -rdynamic");
                if (err) {
                    throw std::runtime_error("Unable to compile query.");
                }

                auto code_compilation_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - code_compilation_begin).count();
                //---------------------------------------------------------------------------------------

                //---------------------------------------------------------------------------------------
                auto query_execution_begin = std::chrono::steady_clock::now();

                ExecuteQuery(db, "../tools/queryc/gen/query.so");

                auto query_execution_duration = std::chrono::duration_cast<std::chrono::milliseconds>(
                        std::chrono::steady_clock::now() - query_execution_begin).count();
                //---------------------------------------------------------------------------------------

                if (enable_stats) {
                    std::cout << "-----" << std::endl;
                    std::cout << "Parsing SQL:     " << parse_query_duration << " ms" << std::endl;
                    std::cout << "Generating code: " << code_generation_duration << " ms" << std::endl;
                    std::cout << "Compiling query: " << code_compilation_duration << " ms" << std::endl;
                    std::cout << "Query execution: " << query_execution_duration << " ms" << std::endl;
                }
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
            }
        }

        // Print prompt for next input
        std::cout << ">>> " << std::flush;
    }
    return 0;
}
