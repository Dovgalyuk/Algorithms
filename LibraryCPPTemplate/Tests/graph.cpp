#include "graph.h"
#include "vector.h"
#include <algorithm>
#include <iostream>
#include <set>

int main() {
	Graph<int>::GraphType type = Graph<int>::GraphType::Directed;
	///////////Checking the number of vertices///////////////////////
	Graph<int> graph(5,type); 
	
	if (graph.get_VertexAmount() != 5) {
		std::cout << "Invalid  vertex amount\n"<<std::endl;
		return 1;
	}
	else {
		std::cout << "correct number of vertices\n" << std::endl;
	}
	////////////Check that the labels are set correctly////////////////
	for (int i = 0; i < 5; ++i) {
		graph.get_Vertex(i).set_VertexData(i * 10); 
	}
	bool allDataCorrect = true;

	for (size_t i = 0; i < graph.get_VertexAmount(); ++i) {
		int expectedData =(int) i * 10;
		int actualData = graph.get_Vertex(i).get_VertexData();

		if (actualData == expectedData) {
			std::cout << "Vertex " << i << ": Data is correct (" << actualData << ")." << std::endl;
		}
		else {
			std::cerr << "Vertex " << i << ": Expected " << expectedData << ", but got " << actualData << "." << std::endl;
			allDataCorrect = false;
		}
	}
	if (allDataCorrect) {
		std::cout << "All vertex data is correct." << std::endl;
	}
	else {
		return 1; 
	}

	////////////checking the output of all labels(get_AllVertexData())//////////////////////////
	std::vector<int> allData = graph.get_AllVertexData();
	std::cout << "Data for all vertices of the graph:\n" << std::endl;

	bool outputDataCorrect = true;
	for (size_t i = 0; i < graph.get_VertexAmount(); ++i) {
		int expectedData =(int) i * 10;

		if (i < allData.size()) { 
			int actualData = allData[i];
			std::cout << actualData << std::endl; 

			
			if (actualData != expectedData) {
				std::cerr << "Output data mismatch at vertex " << i
					<< ": Expected " << expectedData
					<< ", but got " << actualData << "." << std::endl;
				outputDataCorrect = false;
			}
		}
		else {
			std::cerr << "Output data is missing for vertex\n " << i << "." << std::endl;
			outputDataCorrect = false;
		}
	}

	if (outputDataCorrect) {
		std::cout << "All output data is correct.\n" << std::endl;
	}
	else {
		return 1; 
	}

	///////////////iterator test//////////////////////////////////
	graph.add_Edge(0, 1,10);
	graph.add_Edge(0, 2,4);
	graph.add_Edge(1, 3,7);
	graph.add_Edge(2, 4,5);

	
	for (size_t vertex = 0; vertex < graph.get_VertexAmount(); ++vertex) {
		Graph<int>::Iterator it = graph.get_Iterator(vertex);
		std::set<int> actual;

		while (it.hasNext()) {
			actual.insert((int)it.next());
		}

		std::set<int> expected;
		if (vertex == 0) {
			expected = { 1, 2 }; 
		}
		else if (vertex == 1) {
			expected = { 3 };
		}
		else if (vertex == 2) {
			expected = { 4 }; 
		}

		if (actual == expected) {
			std::cout << "Test passed for vertex " << vertex << ": ";
			for (int v : actual) {
				std::cout << v << " ";
			}
			std::cout << std::endl;
		}
		else {
			return 1;
		}
	}
	////////////Edge removal check//////////////////////////////////////////
	//graph.remove_Edge(0, 1);
	//std::cout << "After deletion:" << std::endl;
	//for (size_t i = 0; i < graph.get_VertexAmount(); ++i) {
	//	std::cout << "Vertex " << i << ": ";
	//	Graph<int>::Iterator it = graph.get_Iterator(i);
	//	while (it.hasNext()) {
	//		std::cout << it.next() << " ";
	//	}
	//	std::cout << std::endl;
	//}

	//bool edgeExists = false;
	//Graph<int>::Iterator it = graph.get_Iterator(0);
	//while (it.hasNext()) {
	//	if (it.next() == 1) {
	//		edgeExists = true; 
	//		break;
	//	}
	//}

	//if (!edgeExists) {
	//	std::cout << "Test passed: Edge (0, 1) was successfully removed." << std::endl;
	//}
	//else {
	//	std::cout << "Test failed: Edge (0, 1) still exists!" << std::endl;
	//	return 1;
	//}
	//
	////////////Vertex removal check//////////////////////////////////////////
	//graph.add_Edge(0, 1, 10);
	//graph.add_Edge(2, 3, 5);
	//graph.add_Edge(0, 4, 1);

	//int index1 = 3; 
	//std::cout << "Deleting a vertex with an index: " << index1 << std::endl;
	//graph.remove_Vertex(index1);
	//if (graph.get_VertexAmount() != 4) {
	//	std::cout << "Invalid vertex deletion" << std::endl;
	//	return 1;
	//}
	//else {
	//	std::cout << "valid vertex removal" << std::endl;
	//}

 
return 0;
}
