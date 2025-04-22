#include <iostream>
#include <vector>

using namespace std;

int main() {
    // Define constants
    const int T = 1, F = 0;
    vector<vector<int>> X = {{T, T}, 
                            {T, F}, 
                            {F, T}, 
                            {F, F}};
    vector<int> Y = {T, F, F, F};
    vector<double> Ws = {0.0, 0.0};
    double bias = 0.5;
    const int epoch = 20;
    const double learning_rate = 0.1;

    // Define step function
    auto step_fun = [](double summation) {
        return summation > 0 ? 1 : 0;
    };

    // Train the perceptron
    for (int k = 0; k < epoch; k++) {
        int errors = 0; 

        for (int i = 0; i < X.size(); i++) {
            double summation = 0;
            for (int j = 0; j < X[i].size(); j++) {
                summation += X[i][j] * Ws[j];
            }
            summation += bias;
            int y_pred = step_fun(summation);
            int error = Y[i] - y_pred;

            if (error != 0) {
                errors++; 
            }

            
            for (int j = 0; j < Ws.size(); j++) {
                Ws[j] += error * learning_rate * X[i][j];
            }
            bias += error * learning_rate;
        }

        
        double error_rate = static_cast<double>(errors) / X.size();
        cout << "Epoch " << k + 1 << ": Error Rate = " << error_rate * 100 << "%" << endl;
    }

    
    cout << "Final weights: [" << Ws[0] << ", " << Ws[1] << "]" << endl;
    cout << "Final bias: " << bias << endl;

    
    for (int i = 0; i < X.size(); i++) {
        double summation = 0;
        for (int j = 0; j < X[i].size(); j++) {
            summation += X[i][j] * Ws[j];
        }
        summation += bias;
        int y_pred = step_fun(summation);
        cout << "Input: [" << X[i][0] << ", " << X[i][1] << "], Predicted: " << y_pred << ", Actual: " << Y[i] << endl;
    }

    return 0;
}