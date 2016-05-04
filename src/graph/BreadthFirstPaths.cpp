/*
 * BreadthFisrtPaths.cpp
 *
 *  Created on: 8 febr. 2016
 *      Author: roure
 */

#include "BreadthFirstPaths.h"
#include <queue>
#include <iostream>

namespace std {


BreadthFirstPaths::BreadthFirstPaths(AdjListGraph & g, int s) {
	visited = new bool[g.getSize()];
	for (int i=0; i<g.getOrder(); i++) {
		visited[i]=false;
	}

	edgeTo = new int[g.getSize()];
	this->s = s;
	bfs(g,s);
}

BreadthFirstPaths::~BreadthFirstPaths() {
	delete[]  visited;
	delete[]  edgeTo;
}

void BreadthFirstPaths::bfs(AdjListGraph & g, int v) {
	queue<int> needToProcess;

	visited[v] = true;
	needToProcess.push(v);
	while (!needToProcess.empty()) {
		int w = needToProcess.front();
		needToProcess.pop();
		cout << "removes from queue " << w << endl;
		for (int u : g.adj(w)) {
			if (!visited[u]) {
				edgeTo[u] = w;
				visited[u] = true;
				needToProcess.push(u);
				cout << "adds " << u << " to queue" << endl;
			}
		}
	}
}


bool BreadthFirstPaths::hasPathTo(int v) {
	return visited[v];
}

list<int> BreadthFirstPaths::pathTo(int v) {
	list<int> path;

	if (!hasPathTo(v)) {
		path.push_back(-1);
		return path; //there is no path
	}

	for (int x = v; x !=s; x=edgeTo[x]) {
		path.push_back(x);
	}
	path.push_back(s);

	return path;
}


int BreadthFirstPaths::numConnected() {
	return this->count;
}


} /* namespace std */
