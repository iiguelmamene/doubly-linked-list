#include "Sequence.h"
#include <iostream>
    Sequence::Sequence()
	: m_size(0) // set size to 0
	{
		head = nullptr;
		tail = nullptr; // head and tail set to nullptr for empty sequence
	}
	Sequence::Sequence(const Sequence& other)
	{
		m_size = 0;
		head = nullptr;
		tail = nullptr; // creates empty sequence
		Node* p = other.head; // create reference point to other's head
		for (int i = 0; i < other.m_size; i++) // loop through to insert each of other's values into new sequence
		{
			insert(i, p->val);
			p = p->next;
		}
	}

	Sequence& Sequence::operator=(const Sequence& rhs)
	{
		if (this != &rhs) // test case to make sure there is no aliasing mishap
		{
			Sequence temp(rhs); // copies rhs into new sequence called temp
			swap(temp); // swap this and temp
		}
		return *this; // this now holds what rhs held, return what this points to
	}
	Sequence::~Sequence()
	{
		Node* gr;
		gr = head; // create reference point to the head of the sequence
		while (gr != nullptr) // loop through every node
		{
			Node* newn = gr->next; // save next node before deleting so as to avoid accessing bad data
			delete gr; // delete node
			gr = newn; // move on to next node
		}
	}
	bool Sequence::empty() const
	{
		return size() == 0; // return whether or not size is equal to 0
	}
	int Sequence::size() const
	{
		return m_size; // return size of sequence
	}
	bool Sequence::insert(int pos, const ItemType& value)
	{
		if (pos < 0)
			return false; // pos cannot be negative
		if (pos > size()) 
			return false; // pos cannot be greater than size
		if (size() == 0 && pos == 0) // case of inserting to empty sequence
		{
			Node* p = new Node; // create new node
			p->val = value; // set node's value to value
			p->next = nullptr; // the next value is currently nonexistent
			p->prev = nullptr; // this is only node right now, so no prev. and next node
			head = p;
			tail = p; // head and tail point to same node
			m_size++;
			return true;
		}
		if (pos == 0) // insert to front of sequence
		{
			Node* p = new Node;
			p->val = value;
			p->next = head; // new first node's next is old first node
			(p->next)->prev = p; // old first node's prev. is the new first node
			p->prev = nullptr; // new first node does not have a prev. node
			head = p; // head points to inserted node
			m_size++;
			return true;
		}
		if (pos == size()) // insert to end of sequence
		{
			Node* p = new Node;
			p->val = value;
			p->next = nullptr; // no next node
			p->prev = tail; // new last node's prev. node is the old last node
			(p->prev)->next = p; // new last node's prev. node is the new last node
			tail = p; // tail points to inserted node
			m_size++;
			return true;
		}

		if (pos > 0 && pos < size())
		{
			Node* p = head;
			for (int i = 0; i < pos - 1; i++) // loop until one above desired position
			{
				p = p->next;
			}
			Node* latest = new Node;
			latest->val = value; // set new node's value
			latest->next = p->next;         // set new node's next and prev. pointers
			p->next = latest;               // as well as adjusting the previous node's next pointer
			latest->prev = p;               // and the next node's previous pointer
			(latest->next)->prev = latest;
			m_size++;
			return true;
		}
		return false;
	}
	int Sequence::insert(const ItemType& value)
	{
		if (size() == 0)
		{
			insert(0, value); // if size is 0, insert to front of sequence
			return 0;
		}
		Node* p = head;
		int i = 0;
		for (i; i < size(); i++)
		{
			if (value <= p->val) // look for first pos. where value is less than or equal to val. at that pos.
				break;
			if (p->next != nullptr) // keep moving on until potentially end of sequence
				p = p->next;
		}
		insert(i, value); // insert at smallest possible pos. the desired value
		return i; // return position at which value was inserted
	}
	bool Sequence::erase(int pos)
	{
		if (pos < 0)     
			return false;
		if (m_size == 0)
			return false;
		if (pos >= m_size)
			return false;
		if (head == nullptr)     // cannot erase val. if sequence is empty, size is 0,
			return false;        // pos. is less than 0, or pos. is greater than or equal to size
		if (pos == 0) // erase node at start of sequence
		{
			Node* des = head; // create reference to first node
			head = des->next; // set head to second node
			delete des; // delete first node
			m_size--;
			if (m_size == 0)
				tail = nullptr; // if sequence is now empty, set tail to nullptr
			return true;
		}
		Node* p = head;
		if (pos == size() - 1) // erase node at end of sequence
		{
			Node* des = tail; // reference to last node
			tail = des->prev; // // set tail to point to second to last node
			(des->prev)->next = nullptr; // set second to last node's next ptr. to nullptr
			delete des; // delete last node
			m_size--;
			return true;
		}
		else if (pos > 0 && pos < m_size - 1) // delete node somewhere in middle
		{
			int i = 0;
			while (i != pos - 1) // loop until pos. one above desired pos.
			{
				i++;
				p = p->next;
			}
			if (p != nullptr)
			{
				Node* killme = p->next;   // adjust desired deleted prev. node's next ptr. and 
				p->next = killme->next;   // its next node's prev. ptr.
				(p->next)->prev = p;
				delete killme;            // delete desired node
			}
			m_size--;
			return true;
		}
		return false;
	}
	int Sequence::remove(const ItemType& value)
	{
		Node* p = head;
		int i = 0;
		int c = 0;

		for (i; i < size(); i++)
		{		
			if (p->val == value) // loop until desire value is found
			{
				p = p->next; // move to next node before node is deleted so as to avoid accessing bad data
				erase(i); // erase node at position at which desired value is found
				c++;
				i--; // subtract one from position so process can be repeated correctly
			}
			else
			{
				p = p->next; // move on to next node
			}
		}
		return c; // return how many times a node is deleted
	}
	bool Sequence::get(int pos, ItemType& value) const
	{
		if (pos < 0)
			return false; // pos. can not be negative
		if (pos >= size())
			return false; // pos. cannot be greater than equal to size
		if (pos == 0)
		{
			Node* p = head;
			value = p->val; // set value to first node's value if pos. is 0
			return true;
		}

		int i = 0;
		Node* p = head;
		for (i; i < pos; i++) // loop until one before the desired pos.
		{
			if (p->next != nullptr)
				p = p->next; // move onto next node each iteration of loop, until
		}                    // node at pos. is reached at last iteration
		value = p->val; // set value to val. at position pos.
		return true;
	}
	bool Sequence::set(int pos, const ItemType& value)
	{
		if (pos < 0)
			return false; // pos. cannot be negative
		if (pos >= size())
			return false; // pos. cannot be greater than or equal to size
		Node* p = head; // reference to start of sequence
		if (pos == 0)
			p->val = value; // if pos. is 0, set node's val. to value
		int i = 0;
		for (i; i < pos; i++) // loop until position pos. is reached in sequence of nodes
		{
			if (p->next != nullptr)
				p = p->next; // move on to next node each iteration
		}
		p->val = value; // set node at position pos.'s value to value
		return true;
	}
	int Sequence::find(const ItemType& value) const
	{
		Node* p = head;
		for (int i = 0; i < size(); i++) // loop through each node in sequence
		{
			if (p->val == value)
				return i; // return smallest pos. at which node's val. equals value
			if (p->next != nullptr)
				p = p->next; // move onto next node
		}
		return -1; // return -1 is value not found
	}
	void Sequence::swap(Sequence& other)
	{
		Node* temph = head;       // swap pointers to head and tails of the sequences, as
		Node* tempt = tail;       // well as the sizes of the sequences
		head = other.head;
		tail = other.tail;
		other.head = temph;
		other.tail = tempt;
		int temp = size();
		m_size = other.size();
		other.m_size = temp;
	}

	int subsequence(const Sequence& seq1, const Sequence& seq2)
	{
		if (&seq1 == &seq2)
			return 0; // if sequences are same, start of subsequence is pos. 0
		if (seq2.size() > seq1.size())
			return -1; // seq2 cannot be a part of seq1 if its length is > seq1's
		if (seq2.size() == 0)
			return -1; // no possible subsequence is seq2 has no nodes
		ItemType init;
		seq2.get(0, init); // set init to seq2's first node's value
		ItemType findit;
		ItemType foundit;
		int initpos;
		int length = seq2.size();
		if (seq1.find(init) == -1) 
			return -1; // return -1 if first val. of seq2 cannot be found at all in seq1
		initpos = seq1.find(init);
		Sequence temp = seq1;
		if (initpos + length > temp.size())
			return -1;
		int i = 0;
		int count = 0;
		int c = initpos;
		for (c; c < initpos + length; c++) // start at pos. at which first val. of seq2 is found in seq1
		{
			seq2.get(i, findit);
			temp.get(c, foundit);
			if (findit == foundit) // check if values of seq2 are found consecutively in seq1
			{
				i++;
				if (i == length)              // once all of seq1 is found consecutively in seq1, return pos. at which
					return (initpos + count); // first val. of seq2 is found in seq1
			}
			else
			{
				temp.erase(initpos);         // find next pos. at which first val. of seq2 is found in seq1
				count++;                     // if this position does not exist, return -1
				initpos = temp.find(init);   // restart loop of searching for seq2 within seq1
				if (initpos == -1)
					return -1;
				i = 0;
				c = initpos - 1;
				if (initpos + length > temp.size())
					return -1;
			}
		}
		return initpos + count; // return position of beginning of seq2 within seq1
	}                          

	void interleave(const Sequence& seq1, const Sequence& seq2, Sequence& result)
	{
		Sequence temp; // create an empty sequence 
		if (seq1.size() == 0 && seq2.size() > 0) // only seq2 contains meaningful values
			temp = seq2; 
		else if (seq2.size() == 0 && seq1.size() > 0) // only seq1 contains meaningful values
			temp = seq1;
		else if (seq1.size() == 0 && seq2.size() == 0) // neither seq1 nor seq2 contains any meaningful values
			temp = seq1;
		else if (seq1.size() == seq2.size()) // if seq1 and seq2 are the same size
		{
			int i = 0;
			int c = 0;
			while (i != seq2.size()) // until we reach the end of seq2
			{
				ItemType seq1val;
				ItemType seq2val;
				seq1.get(i, seq1val);     // get values at position "i" in seq1 and seq2
				seq2.get(i, seq2val);
				temp.insert(c, seq1val);  // insert seq1's "i"th value into temp; then, 
				c++;                      // enter seq2's "i"th value into temp
				temp.insert(c, seq2val);
				c++;
				i++;
			}
		}
		else if (seq1.size() > seq2.size()) // if seq1's size is > seq2's size
		{
			int i = 0;
			int c = 0;
			while (i != seq2.size()) // run through until the end of seq2 is reached
			{
				ItemType seq1val;
				ItemType seq2val;
				seq1.get(i, seq1val);
				seq2.get(i, seq2val);     // get values at position "i" in seq1 and seq2
				temp.insert(c, seq1val);  // insert seq1's "i"th value into temp; then, 
				c++;                      // enter seq2's "i"th value into temp
				temp.insert(c, seq2val);
				c++;
				i++;
			}
			int y = 2 * seq2.size(); // seq2's end has been reached but seq1's hasn't 
			int ys = seq2.size();    
			int m_max = seq1.size() + seq2.size();
			for (y; y < m_max; y++)                    // continue adding  to temp, starting at 
			{                                          // pos. y, until pos. m_max - 1
				ItemType m_enter;
				seq1.get(ys, m_enter);
				temp.insert(y, m_enter); // insert the rest of seq1's values into temp
				ys++;
			}
		}
		else if (seq2.size() > seq1.size()) // if seq2's size is > seq1's size
		{
			int i = 0;
			int c = 0;
			while (i != seq1.size()) // run through until the end of seq1 is reached
			{
				ItemType seq1val;
				ItemType seq2val;
				seq1.get(i, seq1val);
				seq2.get(i, seq2val);       // get values at position "i" in seq1 and seq2
				temp.insert(c, seq1val);    // insert seq1's "i"th value into temp; then,
				c++;                        // enter seq2's "i"th value into temp
				temp.insert(c, seq2val);
				c++;
				i++;
			}
			int y = 2 * seq1.size(); // seq1's end has been reached but seq2's hasn't
			int ys = seq1.size();
			int m_max = seq1.size() + seq2.size();
			for (y; y < m_max; y++)                // continue adding  to temp, starting at
			{                                      // pos. y, until pos. m_max - 1
				ItemType m_enter;
				seq2.get(ys, m_enter);
				temp.insert(y, m_enter); // insert the rest of seq2's values into temp
				ys++;
			}
		}
		result = temp; // set result equal to temp
	}

	
