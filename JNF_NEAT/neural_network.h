#pragma once
#include "gene.h"
#include "neuron.h"
#include "genome.h"
#include <vector>

class NeuralNetwork {
	private:
		Genome genome;
		std::vector<Neuron> neurons;
		std::vector<Neuron*> inputNeurons;
		std::vector<Neuron*> outputNeurons;
		const TrainingParameters& parameters;

	public:
        NeuralNetwork() = delete;
		explicit NeuralNetwork(const TrainingParameters& parameters);
        explicit NeuralNetwork(const Genome& genome);
        explicit NeuralNetwork(Genome&& genome);
        explicit NeuralNetwork(const Genome&& genome) = delete;
		NeuralNetwork(const NeuralNetwork& other);
		NeuralNetwork(NeuralNetwork&& other);
		~NeuralNetwork() = default;

		NeuralNetwork& operator= (const NeuralNetwork& other);

		const Genome& GetGenome() const { return genome; }

		void SetInputs(const std::vector<float>& inputs);
		std::vector<float> GetOutputs();

	private:
		void MutateGenesAndBuildNetwork();
		static bool DidChanceOccure(float chance);
        static size_t GetRandomNumberBetween(size_t min, size_t max);
		void BuildNetworkFromGenes();
		void InterpretInputsAndOutputs();
		bool ShouldAddNeuron() const { return DidChanceOccure(parameters.advanced.mutation.chanceForNeuralMutation); }
		bool ShouldAddConnection() const { return DidChanceOccure(parameters.advanced.mutation.chanceForConnectionalMutation); }
		bool ShouldMutateWeight() const { return DidChanceOccure(parameters.advanced.mutation.chanceForWeightMutation); }
		void AddRandomNeuron();
		void AddRandomConnection();
		void ShuffleWeights();
		void MutateWeightOfGeneAt(std::size_t index);
		void PerturbWeightAt(std::size_t index);
        void CategorizeNeuronsIntoLayers();
		void CategorizeNeuronBranchIntoLayers (Neuron& currNode, size_t& currLayer);
};