#include "HuffmanTree.h"
#include <queue>

HuffmanTree::HuffmanTree() : root(nullptr) {}

std::unordered_map<char, int> HuffmanTree::buildFrequencyTable(const std::string& text) {
    std::unordered_map<char, int> freq;
    for (char c : text) freq[c]++;
    return freq;
}

void HuffmanTree::build(const std::string& text) {
    auto freq = buildFrequencyTable(text);
    std::priority_queue<Node*, std::vector<Node*>, Compare> pq;

    for (auto& pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() > 1) {
        Node* left  = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        Node* parent = new Node('\0', left->freq + right->freq);
        parent->left  = left;
        parent->right = right;
        pq.push(parent);
    }

    root = pq.top();
    generateCodes(root, "");
}

void HuffmanTree::generateCodes(Node* node, const std::string& path) {
    if (!node) return;
    if (!node->left && !node->right) {
        codes[node->ch] = path;
        return;
    }
    generateCodes(node->left,  path + "0");
    generateCodes(node->right, path + "1");
}

void HuffmanTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

HuffmanTree::~HuffmanTree() {
    deleteTree(root);
}