#pragma once
#include "matrix.h"
#include "isubsampler.h"
#include <vector>

namespace Convolutional {
namespace SubSampler {

class Neuron : public ISubSampler {
public:
	Neuron(double bias, std::vector<double>&& weights) : bias(bias), weights(std::move(weights)) {}

	auto ProcessMatrix(Matrix::Position position, const Matrix& matrix) const -> Matrix override;
	auto GetReceptiveField() const noexcept -> Matrix::Size override { return receptiveField; }
	auto GetZeroPadding() const noexcept -> Matrix::Size override { return zeroPadding; }
	auto GetStride() const noexcept -> Matrix::Size override { return stride; }

	auto GetBias() const noexcept { return bias; }
	auto GetWeights() const noexcept { return weights; }

private:
	static auto sigmoid(Matrix::elementType n) -> double;

	Matrix::Size receptiveField;
	Matrix::Size zeroPadding;
	Matrix::Size stride;

	double bias = 0;
	std::vector<double> weights;
};

}
}
