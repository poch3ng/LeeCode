// Runtime: 12 ms, faster than 16.26% of C++ online submissions for Binary Tree Level Order Traversal.
// Memory Usage: 12.3 MB, less than 96.02% of C++ online submissions for Binary Tree Level Order Traversal.
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        // BFS O(n)
        return BFS(root);
    }
    
private: 
    vector<vector<int>> BFS(TreeNode* root){
        vector<vector<int>> ans;
        vector<TreeNode*> curr, next;
        
        if(root) curr.push_back(root);
        while(!curr.empty()){
            // variable to store the level elements
            vector<int> level;
            for(TreeNode* node : curr){
                // store element to variable
                level.push_back(node->val);
                // get the left node pointer
                if(node->left) next.push_back(node->left);
                // get the right node pointer
                if(node->right) next.push_back(node->right);                
            }
            ans.push_back(level);
            // set next to curr
            curr.swap(next);
            next.clear();
        }
        
        return ans;
    }
};