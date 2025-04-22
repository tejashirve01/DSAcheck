#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

class NeuralNetworkWithBackpropagation {
private:
    std::vector<std::vector<double>> hiddenWeights;
    std::vector<double> outputWeights;
    std::vector<double> hiddenLayerOutputs;
    double learningRate;
    int inputSize;
    int hiddenLayerSize; 

    double sigmoid(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }

    double sigmoidDerivative(double x) {
        return x * (1 - x);
    }

public:
    NeuralNetworkWithBackpropagation(int inputSize, int hiddenLayerSize, double learningRate)
        : inputSize(inputSize), hiddenLayerSize(hiddenLayerSize), learningRate(learningRate) {

        hiddenWeights.resize(hiddenLayerSize, std::vector<double>(inputSize + 1));
        outputWeights.resize(hiddenLayerSize + 1);
        hiddenLayerOutputs.resize(hiddenLayerSize);

        std::srand(static_cast<unsigned int>(std::time(nullptr)));

        for (int i = 0; i < hiddenLayerSize; ++i) {
            for (int j = 0; j < inputSize + 1; ++j) {
                hiddenWeights[i][j] = static_cast<double>(std::rand()) / RAND_MAX - 0.5;
            }
        }

        for (int i = 0; i < hiddenLayerSize + 1; ++i) {
            outputWeights[i] = static_cast<double>(std::rand()) / RAND_MAX - 0.5;
        }
    }

    double forward(const std::vector<double>& inputs) {
        for (int i = 0; i < hiddenLayerSize; ++i) {
            double sum = hiddenWeights[i][0]; // bias
            for (int j = 0; j < inputSize; ++j) {
                sum += inputs[j] * hiddenWeights[i][j + 1];
            }
            hiddenLayerOutputs[i] = sigmoid(sum);
        }

        double output = outputWeights[0]; // bias
        for (int i = 0; i < hiddenLayerOutputs.size(); ++i) {
            output += hiddenLayerOutputs[i] * outputWeights[i + 1];
        }
        return sigmoid(output);
    }

    void backpropagate(const std::vector<double>& inputs, double expectedOutput) {
        double predictedOutput = forward(inputs);

        double outputError = expectedOutput - predictedOutput;

        std::vector<double> hiddenErrors(hiddenLayerOutputs.size());
        for (int i = 0; i < hiddenLayerOutputs.size(); ++i) {
            hiddenErrors[i] = outputError * sigmoidDerivative(predictedOutput) * outputWeights[i + 1];
        }

        
        outputWeights[0] += learningRate * outputError * sigmoidDerivative(predictedOutput);
        for (int i = 0; i < hiddenLayerOutputs.size(); ++i) {
            outputWeights[i + 1] += learningRate * outputError * sigmoidDerivative(predictedOutput) * hiddenLayerOutputs[i];
        }

        
        for (int i = 0; i < hiddenLayerOutputs.size(); ++i) {
            for (int j = 0; j < inputSize; ++j) {
                hiddenWeights[i][j + 1] += learningRate * hiddenErrors[i] * sigmoidDerivative(hiddenLayerOutputs[i]) * inputs[j];
            }
            hiddenWeights[i][0] += learningRate * hiddenErrors[i] * sigmoidDerivative(hiddenLayerOutputs[i]);
        }
    }
};

int main() {
    std::vector<std::vector<double>> inputs = {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
    };
    std::vector<double> outputs = {0, 1, 1, 0}; 

    NeuralNetworkWithBackpropagation nn(2, 2, 0.5);

    std::srand(static_cast<unsigned int>(std::time(nullptr))); 

    for (int epoch = 0; epoch < 10000; ++epoch) {
        int randomIndex = std::rand() % inputs.size();  
        nn.backpropagate(inputs[randomIndex], outputs[randomIndex]); 
    }

    // Testing the network
    std::cout << "Predictions for XOR gate after training:\n";
    for (int i = 0; i < inputs.size(); ++i) {
        double prediction = nn.forward(inputs[i]);
        std::cout << "Input: (" << inputs[i][0] << ", " << inputs[i][1] << ") -> Prediction: " << prediction << std::endl;
    }

    return 0;
}
