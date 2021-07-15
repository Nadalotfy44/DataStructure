#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;
//bitfield//
struct save
{
	unsigned int s :	1;
};
// A Tree node
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// Function to allocate a new tree node
Node* TreeNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

void encode(Node* root, string str,
	unordered_map<char, string>& code)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		code[root->ch] = str;
	}

	encode(root->left, str + "0", code);
	encode(root->right, str + "1", code);
}

// traverse the Tree and decode the encoded string
void decode(Node* root, int& i, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	i++;

	if (str[i] == '0')
		decode(root->left, i, str);
	else
		decode(root->right, i, str);
}

// Builds Tree and decode given input text
void EncodingTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	vector <Node*>pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push_back(TreeNode(pair.first, pair.second, nullptr, nullptr));
		sort(pq.begin(), pq.end(), [](Node* l, Node* r) {
			return l->freq < r->freq;
			});
	}

	
	while (pq.size() != 1)
	{
		// Remove the two nodes of lowest frequency from the queue
		Node* left = pq.front(); pq.erase(pq.begin());
		sort(pq.begin(), pq.end(), [](Node* l, Node* r) {
			return l->freq < r->freq;
			});
		Node* right = pq.front(); pq.erase(pq.begin());
		sort(pq.begin(), pq.end(), [](Node* l, Node* r) {
			return l->freq < r->freq;
			});
		// Create a new sum node with these two nodes
		
		int sum = left->freq + right->freq;
		pq.push_back(TreeNode('\0', sum, left, right));
		sort(pq.begin(), pq.end(), [](Node* l, Node* r) {
			return l->freq < r->freq;
			});
	}

	// root stores pointer to root of Encoding Tree
	Node* root = pq.front();

	// traverse the Tree and store encoding Codes
	// in a map. Also prints them
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// traverse the Tree to decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}

// Huffman coding algorithm
int main()
{
	string text = "xxxyyyyzzzzzwwwwwww";
	save x = {2};
	
	cout << x.s;
	EncodingTree(text);

	return 0;
}
