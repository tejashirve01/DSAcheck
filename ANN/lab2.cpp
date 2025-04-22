#include <vector>
#include <cmath>

struct Vector {
    std::vector<double> v;
    Vector() : v() {} 
    Vector(int s) : v(s) {}
};

double step_fun(double act) {
    return act > 0 ? 1 : 0;
}

int main() {
    int T = 1, F = 0;
    Vector X[2];
    X[0].v.push_back(T); 
    X[1].v.push_back(F); 
    Vector Y[2];
    Y[0].v.push_back(T);
    Y[1].v.push_back(F);
    Vector Ws(2);
    double bias = 0.5;
    int epoch = 100;
    double learning_rate = 0.1;

    for (int loop = 0; loop < epoch; loop++) {
        for (int i = 0; i < 2; i++) {
            double summation = X[i].v[0] * Ws.v[0] + X[i].v[1] * Ws.v[1] + bias;
            double Y_pred = step_fun(summation);
            double error = Y[i].v[0] - Y_pred;
            Ws.v[0] += error * learning_rate * X[i].v[0];
            Ws.v[1] += error * learning_rate * X[i].v[1];
            bias += error * learning_rate;
        }
    }

    return 0;
}