#include <bits/stdc++.h>
#include <matplot/matplot.h>

#define N_INIT 10
#define N_END 30

int bruteForce(std::vector<std::vector<int>> A, int m, int n){
    int ans = A[0][0];

    for(int i0=0; i0<m; ++i0)
        for(int j0=0; j0<n; ++j0)
            for(int i1=i0; i1<m; ++i1)
                for(int j1=j0; j1<n; ++j1){
                    int curr = 0;
                    for(int i=i0; i<=i1; ++i)
                        for(int j=j0; j<=j1; ++j)
                            curr += A[i][j];
                    ans = std::max(ans, curr);
                }

    return ans;
}

int kadane1D(int *A, int n){
    int ans = A[0], curr = 0;

    for(int i = 0; i<n; ++i){
        curr += A[i];
        curr = std::max(A[i], curr);
        ans = std::max(ans, curr);
    }

    return ans;    
}

int kadane2D(std::vector<std::vector<int>> A, int m, int n){
    int ans = A[0][0];
    int tmp[1024];

    for(int l=0; l<n; ++l){
        memset(tmp, 0, 1024);
        for(int r=l; r<n; ++r){
            for(int i=0; i<m; ++i)
                tmp[i] += A[i][r];
            int sum = kadane1D(tmp, n);
            ans = std::max(ans, sum);
        }
    }

    return ans;
}

int main() {

    std::vector<long long> x_axis, y_bf, y_k;

    for(int i = N_INIT; i<=N_END; ++i)
        x_axis.push_back(i);

    for(int n = N_INIT; n<=N_END; ++n){
        long long avg_bf = 0, avg_k = 0;
        for(int t=0; t<20; ++t){
            
            std::vector<std::vector<int>> V;
            for (int i = 0; i < n; ++i){
                V.push_back(std::vector<int>());
                for (int j = 0; j < n; ++j){
                    V[i].push_back(-rand()%100);
                    if(rand()%20<t)
                        V[i][j] *= -1;
                }
            }

            auto start_bf = std::chrono::high_resolution_clock::now();
            bruteForce(V, n, n);
            auto end_bf = std::chrono::high_resolution_clock::now();
            auto duration_bf = std::chrono::duration_cast<std::chrono::nanoseconds>(end_bf-start_bf).count();
            avg_bf += duration_bf;
            
            auto start_k = std::chrono::high_resolution_clock::now();
            kadane2D(V, n, n);
            auto end_k = std::chrono::high_resolution_clock::now();
            auto duration_k = std::chrono::duration_cast<std::chrono::nanoseconds>(end_k-start_k).count();
            avg_k += duration_k;

        }
        std::cout << n << " -> " << avg_bf/20 << " " << avg_k/20 << "\n";
        y_bf.push_back(avg_bf/20);
        y_k.push_back(avg_k/20);
    }

    matplot::xlabel("N");
    matplot::ylabel("nanoseconds");
    auto p_bf = matplot::plot(x_axis, y_bf, "-o");
    p_bf->display_name("Brute Force");
    p_bf->line_width(3);
    matplot::hold(true);
    auto p_k = matplot::plot(x_axis, y_k, "--xr");
    p_k->display_name("Kadane 2D");
    p_k->line_width(3);
    matplot::hold(false);
    matplot::legend(true);
    matplot::show();

    return 0;
}