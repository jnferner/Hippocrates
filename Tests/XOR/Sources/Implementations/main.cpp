#include <iostream>
#include <fstream>
#include <chrono>

// TODO: Replace with library import
#include "../../../../Core/Sources/Headers/neural_network_trainer.h"

using namespace std;
using namespace JNF_NEAT;

enum class XORResult {
	Zero,
	One,
	ClassificationCount
};

template <typename InputType, typename Classification>
auto TestNetwork(NeuralNetwork &network, TrainingData<InputType, Classification> &data) {
	int errorCount = 0;

	for (const auto& dataSet: data) {
		auto networkOutputs = network.GetOutputsUsingInputs(dataSet.input);

		auto maxOutput = std::max_element(networkOutputs.begin(), networkOutputs.end());
		auto outputIndex = std::distance(networkOutputs.begin(), maxOutput);

		if (outputIndex != static_cast<size_t>(dataSet.classification)) {
			std::cout << "Incorrect classification for inputs:";
			for (auto& input: dataSet.input) {
				std::cout << " - " << input << std::endl;
			}

			std::cout << "Got outputs:";
			for (auto& output: networkOutputs) {
				std::cout << " - " << output << std::endl;
			}

			std::cout << std::endl;
		}
	}

	return errorCount;
}

auto SaveNetwork(TrainedNeuralNetwork &champ, string filename) {
	ofstream outFile(filename);
	champ.SaveToFile(outFile);
	outFile.close();
}

auto LoadNetwork(string filename) {
	ifstream inFile(filename);
	auto champ = TrainedNeuralNetwork::LoadFromFile(inFile);
	inFile.close();

	return champ;
}

int main() {
	srand(static_cast<unsigned>(time(nullptr)));

	TrainingData<std::vector<float>, XORResult> data;
	data.AddSet({ {0.0f, 0.0f}, XORResult::Zero });
	data.AddSet({ {0.0f, 1.0f}, XORResult::One });
	data.AddSet({ {1.0f, 0.0f}, XORResult::One });
	data.AddSet({ {1.0f, 1.0f}, XORResult::Zero });

	NeuralNetworkTrainer trainer;
	trainer.loggingEnabled = false;

	#ifdef CI
		trainer.loggingEnabled = false;
	#endif

	auto champ = trainer.TrainSupervised(data, 50);

	SaveNetwork(champ, "champ.nn");
	LoadNetwork("champ.nn");

	return TestNetwork(champ, data);
}