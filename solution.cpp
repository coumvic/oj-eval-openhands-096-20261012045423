#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Global map to store node depth and parent
unordered_map<int, pair<int, int>> nodeInfo; // node_val -> (depth, parent_val)

// Build binary tree from preorder traversal
TreeNode* buildTree(vector<int>& preorder, int& index) {
    if (index >= preorder.size()) {
        return nullptr;
    }
    
    int val = preorder[index++];
    if (val == -1) {
        return nullptr;
    }
    
    TreeNode* root = new TreeNode(val);
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    
    return root;
}

// Traverse tree to record depth and parent information
void recordNodeInfo(TreeNode* node, int depth, int parent) {
    if (!node) return;
    
    nodeInfo[node->val] = {depth, parent};
    
    recordNodeInfo(node->left, depth + 1, node->val);
    recordNodeInfo(node->right, depth + 1, node->val);
}

// Check if two nodes are cousins
bool areCousins(int x, int y) {
    if (nodeInfo.find(x) == nodeInfo.end() || nodeInfo.find(y) == nodeInfo.end()) {
        return false;
    }
    
    auto infoX = nodeInfo[x];
    auto infoY = nodeInfo[y];
    
    // Same depth and different parents
    return infoX.first == infoY.first && infoX.second != infoY.second;
}

// Free memory
void deleteTree(TreeNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int q;
    cin >> q;
    
    vector<pair<int, int>> queries;
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        queries.push_back({x, y});
    }
    
    // Read the entire remaining line for preorder traversal
    string line;
    vector<int> preorder;
    
    // Read all remaining numbers
    while (cin >> line) {
        stringstream ss(line);
        int num;
        ss >> num;
        preorder.push_back(num);
    }
    
    // Build the tree
    int index = 0;
    TreeNode* root = buildTree(preorder, index);
    
    // Record node information
    recordNodeInfo(root, 0, -1); // root has parent -1
    
    // Process queries
    for (auto& query : queries) {
        cout << (areCousins(query.first, query.second) ? 1 : 0) << '\n';
    }
    
    // Clean up
    deleteTree(root);
    
    return 0;
}