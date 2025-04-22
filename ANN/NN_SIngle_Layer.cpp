#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class NeuralNetworkSingleLayer {
private:
    std::vector<std::vector<double>> hiddenWeights;
    std::vector<double> hiddenLayerOutputs;
    int inputSize;
    int hiddenLayerSize;

    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }

public:
    NeuralNetworkSingleLayer(int inputSize, int hiddenLayerSize)
        : inputSize(inputSize), hiddenLayerSize(hiddenLayerSize) {
        hiddenWeights.resize(hiddenLayerSize, std::vector<double>(inputSize + 1));
        hiddenLayerOutputs.resize(hiddenLayerSize);

        // Seed for random number generation
        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < hiddenLayerSize; ++i) {
            for (int j = 0; j < inputSize + 1; ++j) {
                hiddenWeights[i][j] = static_cast<double>(std::rand()) / RAND_MAX - 0.5;
            }
        }
    }

    std::vector<double> forward(const std::vector<double>& inputs) {
        for (int i = 0; i < hiddenLayerSize; ++i) {
            double sum = hiddenWeights[i][0]; // bias term
            for (int j = 0; j < inputSize; ++j) {
                sum += inputs[j] * hiddenWeights[i][j + 1];
            }
            hiddenLayerOutputs[i] = sigmoid(sum);
        }
        return hiddenLayerOutputs;
    }
};

int main() {
    std::vector<double> inputs = {1.0, 0.0};

    NeuralNetworkSingleLayer nn(2, 3);

    std::vector<double> hiddenOutputs = nn.forward(inputs);

    std::cout << "Hidden layer outputs:\n";
    for (double output : hiddenOutputs) {
        std::cout << output << " ";
    }
    std::cout << std::endl;

    return 0;
}
