#ifndef SEQUENCE_INCLUDED
#define SEQUENCE_INCLUDED

#include <string>
typedef std::string ItemType;

class Sequence
{
public: // public methods, constructor, and destructor 
	Sequence();
	~Sequence();
	Sequence(const Sequence& other);
	Sequence& operator=(const Sequence& rhs);
	bool empty() const;
	int size() const;
	bool insert(int pos, const ItemType& value);
	int insert(const ItemType& value);
	bool erase(int pos);
	int remove(const ItemType& value);
	bool get(int pos, ItemType& value) const;
	bool set(int pos, const ItemType& value);
	int find(const ItemType& value) const;
	void swap(Sequence& other);
private:
	struct Node
	{
		ItemType val;
		Node* next;
		Node* prev;
	};
	Node* head; // head pointer
	Node* tail; // tail pointer
	int m_size; // size of the linked list
};
int subsequence(const Sequence& seq1, const Sequence& seq2);
void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result);

#endif
