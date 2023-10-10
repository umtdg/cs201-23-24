#!/usr/bin/env bash

set -e

codeql_db="codeql"
codeql_log="codeql.log"
codeql_results_dir="codeql_results"
codeql_dirs=("$codeql_db" "_codeql_build_dir")

queries=(
    "codeql/cpp-queries:Best Practices"
    "codeql/cpp-queries:Critical"
)

if [ -f "$codeql_log" ]; then
    rm -rf "$codeql_log" >/dev/null 2>&1
fi

echo "[+] Creating CodeQL database"
codeql database create --language=cpp "$codeql_db" >"$codeql_log" 2>&1

echo "[+] Create CodeQL results directory"
mkdir -p codeql_results

for query in "${queries[@]}"; do
    query_friendly_name="${query##*:}"
    query_name="${query_friendly_name// /-}"
    query_name="${query_name,,}"

    echo "[+] Analyzing for $query_friendly_name"
    options=(
        database
        analyze
        --format=csv
        "--output=${codeql_results_dir}/${query_name}.csv"
        "$codeql_db"
        "$query"
    )

    codeql "${options[@]}" >"$codeql_log" 2>&1
done

echo "[+] Remove CodeQL database"
rm -rf "${codeql_dirs[@]}" >/dev/null 2>&1
