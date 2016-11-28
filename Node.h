#pragma once

class Entity;

struct Node
{
	Node(const int& x, const int& y)
		: x(x), y(y)
	{
		evaluated = false;
		found = false;
		entity = nullptr;
	}

	Node()
	{
		evaluated = false;
		found = false;
		entity = nullptr;
	}

	bool operator>(const Node& rhs) const
	{
		return distanceTotal > rhs.distanceTotal;
	}
	bool operator==(const Node& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Node& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}

	Node* insert(Node* list)
	{
		if (list == nullptr)
			next = nullptr;
		else
			next = list;

		return this;
	}

	Node* insertSort(Node* list)
	{
		if (list == nullptr)
		{
			prev = nullptr;
			next = nullptr;
			return this;
		}

		prev = nullptr;
		next = list;
		while (next != nullptr)
		{
			if (distanceTotal < next->distanceTotal)
				break;
				
			prev = next;
			next = next->next;
		} 

		if (prev != nullptr)
			prev->next = this;

		if (next != nullptr)
			next->prev = this;

		if (prev == nullptr)
			return this;

		return list;
	}

	Node* sort(Node* list)
	{
		if (prev == nullptr)
		{
			list = next;
			list->prev = nullptr;
		}
		else
		{
			prev->next = next;
		}

		if(next != nullptr)
			next->prev = prev;

		return insertSort(list);
	}

	void reset()
	{
		evaluated = false;
		found = false;
	}

	int x;
	int y;
	float distanceGoal;
	float distanceTraveled;
	float distanceTotal;
	Entity* entity;
	bool evaluated;
	bool found;
	Node* parent;

	Node* next;
	Node* prev;
};

