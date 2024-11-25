#include <bits/stdc++.h>
#include <fstream>
#include <climits>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

#define ll long long

typedef std::vector<ll> vll;
typedef std::vector<std::vector<std::string>> vvs;


void generateTestData(int numMatrices, std::ofstream& output) {
    if (numMatrices < 2) {
        std::cerr << "Count bigger 2." << std::endl;
        return;
    }

    std::srand(std::time(nullptr)); 

    int rows = std::rand() % 1000 + 10;
    int cols;

    for (int i = 0; i < numMatrices; ++i) {
        cols = std::rand() % 1000 + 10; 
        output << rows << " " << cols << std::endl;
        rows = cols; 
    }

}


ll matrixMul1(const vll& dims, ll i, ll j, std::string& result) {
    if (i == j) {
        result = std::to_string(dims[i - 1]) + "x" + std::to_string(dims[i]);
        return 0;
    }

    ll minOperations = LONG_LONG_MAX;
    std::string bestSplit;

    for (int k = i; k < j; ++k) {
        std::string left, right;
        ll leftOps = matrixMul1(dims, i, k, left);
        ll rightOps = matrixMul1(dims, k + 1, j, right);
        ll currentOps = leftOps + rightOps + dims[i - 1] * dims[k] * dims[j];

        if (currentOps < minOperations) {
            minOperations = currentOps;
            bestSplit = "(" + left + "*" + right + ")";
        }
    }

    result = bestSplit;
    return minOperations;
}


ll matrixMul2(const vll& dims, std::string& result) {
    int n = dims.size() - 1;
    std::vector<vll> dp(n, vll(n, 0));
    vvs splits(n, std::vector<std::string>(n));

    for (int i = 0; i < n; ++i) {
        splits[i][i] = std::to_string(dims[i]) + "x" + std::to_string(dims[i + 1]);
    }

    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            dp[i][j] = LONG_LONG_MAX;

            for (int k = i; k < j; ++k) {
                ll cost = dp[i][k] + dp[k + 1][j] + dims[i] * dims[k + 1] * dims[j + 1];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                    splits[i][j] = "(" + splits[i][k] + "*" + splits[k + 1][j] + ")";
                }
            }
        }
    }

    result = splits[0][n - 1];
    return dp[0][n - 1];
}

void solve(std::ifstream& input, std::ofstream& output1, std::ofstream& output2) {
    vll dimensions;
    int rows, cols;
    int n;
    input >> n;
    std::cout << n << std::endl;
    for(int i = 0; i < n; i++) {
        input >> rows >> cols;
        if (dimensions.empty()) {
            dimensions.push_back(rows);
        }
        dimensions.push_back(cols);
    }
    
    if (dimensions.size() < 2) {
        std::cerr << "Invalid size matrix\n";
        return;
    }

    std::string recursiveResult, dpResult;

    auto startRecursive = std::chrono::high_resolution_clock::now();
    ll minOpsRecursive = matrixMul1(dimensions, 1, dimensions.size() - 1, recursiveResult);
    auto endRecursive = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeRecursive = endRecursive - startRecursive;
    output1 << timeRecursive.count() << std::endl;
    output1 << minOpsRecursive << std::endl;

    auto startDP = std::chrono::high_resolution_clock::now();
    ll minOpsDP = matrixMul2(dimensions, dpResult);
    auto endDP = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeDP = endDP - startDP;
    output2 << timeDP.count() << std::endl;
    output2 << minOpsDP << std::endl;

   
    if(minOpsDP != minOpsRecursive) {
        std::cerr << "minOpsDP don't matching minOpsRecursive\n";
        return;
    }
}

int main(int argc, char **argv) {
    std::ofstream inputGen(argv[1]);
    if (!inputGen.is_open()) {
        std::cerr << "Failed to open input file: " << argv[1] << "\n";
        return 1;
    }

    std::ofstream output1(argv[2]);
    if (!output1.is_open()) {
        std::cerr << "Failed to open output file: " << argv[2] << "\n";
        return 1;
    }

    std::ofstream output2(argv[3]);
    if (!output2.is_open()) {
        std::cerr << "Failed to open output file: " << argv[3] << "\n";
        return 1;
    }

    inputGen << 11 << std::endl;

    // For github workflow, on test i'm usage [4;21)
    for(int i = 4; i < 15; i++) {
        inputGen << i << std::endl;
        generateTestData(i, inputGen);
    }

    inputGen.close();
    

    std::ifstream input(argv[1]);
    int t;
    input >> t; 

    while(t--) {
        solve(input, output1, output2);
    }

    input.close();
    output1.close();
    output2.close();

    return 0;
}
