/*
 * Cycle.cpp
 *
 *  Created on: 22 mar� 2016
 *      Author: roure
 */

#include "Cycle.h"
#include <iostream>

namespace std {

Cycle::Cycle(AdjListGraph &g) {
	visited = new bool[g.getOrder()];
	for (int i=0; i<g.getOrder(); i++) {
		visited[i]=false;
	}

	if (hasSelfLoop(g)) return;
	if (hasParallelEdges(g)) return;

	edgeTo = new int[g.getOrder()];
	for (int v=0; v<g.getOrder(); v++) {
		if (!visited[v])
			dfs(g, -1, v);
	}
}

Cycle::~Cycle() {
	delete[]  visited;
	delete[]  edgeTo;
}

void Cycle::dfs(AdjListGraph & g, int u, int v) {
	visited[v] = true;
	for (auto & w : g.adj(v)) {
		if(this->hasCycle()) {
			return;
		}
		else if (!visited[w]) {
			edgeTo[w] = v;
			dfs(g, v, w);
		}
		else if (w != u) { //disregard reverse of edge leading to v
			for (int x = v; x!=w; x=edgeTo[x]) {
				cycle.push(x);
			}
			cycle.push(w);
			cycle.push(v);
		}
	}
}

bool Cycle:: hasCycle() {
	return !cycle.empty();
}

stack<int> & Cycle:: getCycle() {
	return cycle;
}

bool Cycle::hasSelfLoop(AdjListGraph &g) {
	for (int v=0; v < g.getOrder(); v++) {
		for (auto &w : g.adj(v)) {
			if (v==w) {
				cycle.push(v);
				cycle.push(v);
				return true;
			}
		}
	}
	return false;
}

bool Cycle::hasParallelEdges(AdjListGraph &g) {
	for (int v=0; v < g.getOrder(); v++) {
		for (auto &w : g.adj(v)) {
			if (visited[w]) {
				cycle.push(v);
				cycle.push(w);
				cycle.push(v);
				return true;
			}
			visited[w] = true;
		}
	}

	// reset visited
	for (int i=0; i<g.getOrder(); i++) {
		visited[i]=false;
	}

	return false;
}


} /* namespace std */



