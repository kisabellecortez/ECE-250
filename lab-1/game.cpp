#include "game.h"
#include <cmath>
#include <string>

using namespace std;

// implement classes' member functions here...

// constructor
LinkedList::LinkedList()
{
  head = nullptr;
}

// destructor
LinkedList::~LinkedList()
{
  // delete nodes from linked list
  while (head != nullptr)
  {
    delete head;
    head = head->next;
  }
}

// add player to linked list
void LinkedList::spawn(double x, double y)
{
  // don't add player if out of bounds
  if ((x < 0) || (y < 0) || (x > 500) || (y > 500))
  {
    cout << "failure" << endl;
  }
  // add player to front of linked list
  else
  {
    Node *newNode = new Node(x, y);

    newNode->next = head->next;
    head->next = newNode;

    numPlayers += 1;

    cout << "success" << endl;
  }
}

// move players t steps
void LinkedList::time(double t)
{
  Node *curr{head};
  Node *prev{nullptr};

  while (curr != nullptr)
  {
    double tempX = curr->x;
    curr->x -= t * cos(atan2(curr->y, tempX));
    curr->y -= t * sin(atan2(curr->y, tempX));

    // delete player if not in first quadrant
    if ((curr->x < 0) || (curr->y < 0))
    {
      prev->next = curr->next;
      numPlayers--;
    }

    prev = curr;
    curr = curr->next;
  }

  cout << "num of players: " << numPlayers << endl;
}

// delete players < 1 from (0, 0)
void LinkedList::lunch()
{
  Node *curr{head};
  Node *prev{nullptr};

  while (curr != nullptr)
  {
    double d = sqrt(pow(curr->x, 2) + pow(curr->y, 2));

    // remove player from linked list
    if (d < 1)
    {
      prev->next = curr->next;
      numPlayers--;
    }

    prev = curr;
    curr = curr->next;
  }

  cout << "num of players: " << numPlayers << endl;
}

// output number of players
void LinkedList::num()
{
  cout << "num of players " << numPlayers << endl;
}

// print coordinates of players with distance less than d
void LinkedList::prt(double d)
{
  if ((d < 0) || (d > 500))
  {
    int players = 0;

    Node *curr{head};

    // loop through linked list
    while (curr != nullptr)
    {
      double dis = sqrt(pow(curr->x, 2) + pow(curr->y, 2));

      if (dis < d)
      {
        cout << curr->x << " " << curr->y << endl;
        players++;
      }

      curr = curr->next;
    }

    if (players == 0)
    {
      cout << "no players found" << endl;
    }
  }
}

// check for winner then terminate program
void LinkedList::over()
{
  // check if linked list is empty
  if (head == NULL)
  {
    cout << "wolf wins" << endl;
  }
  else
  {
    cout << "players win" << endl;
  }
}