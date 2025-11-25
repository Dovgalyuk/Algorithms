#pragma once
#include "IGraph.h"

template<class VertexType, class EdgeType>
class BaseGraph : public IGraph<VertexType, EdgeType> {
public:
	~BaseGraph() override = default;
};