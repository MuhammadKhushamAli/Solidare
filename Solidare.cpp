#include <iostream>
#include <ctime>
using namespace std;

// Forward Decleration
template <class U>
class Stack;

// Card Class
class Card
{
private:
    int rank;
    bool isRed;
    bool isFlipped;
    string suit;

public:
    // Constructor
    Card(const int RANK, const bool &IS_RED, const string &SUIT) : isFlipped(false)
    {
        rank = RANK;
        isRed = IS_RED;
        suit = SUIT;
        isFlipped = false;
    }

    Card() : rank(0), isRed(false), isFlipped(false)
    {
    }

    // It Compares Rank of Card
    bool operator==(const int &RANK)
    {
        if (rank == RANK)
        {
            return true;
        }
        return false;
    }

    // It Compares Card's Color
    bool operator==(const bool &IS_RED)
    {
        if (isRed == IS_RED)
        {
            return true;
        }
        return false;
    }

    // It Compares Card's String
    bool operator==(const string &SUIT)
    {
        if (suit == SUIT)
        {
            return true;
        }
        return false;
    }

    // It Checks is the Card which is to be Moved Valid to Column
    bool ToColChecker(const Card *CARD_PTR)
    {
        if (CARD_PTR != 0)
        {
            if ((rank == CARD_PTR->rank - 1) && (isRed != CARD_PTR->isRed) && (isFlipped) && (CARD_PTR->isFlipped))
            {
                return true;
            }
        }
        else if (CARD_PTR == 0)
        {
            if (rank == 11)
            {
                return true;
            }
        }
        cout << "Invalid Move" << endl;
        return false;
    }

    // It Checks is the Move Valid To Foundations
    bool ToFoundationChecker(const Card *CARD_PTR)
    {
        if (CARD_PTR != 0)
        {
            if ((rank == CARD_PTR->rank + 1) && (isRed == CARD_PTR->isRed) && (isFlipped) && (CARD_PTR->isFlipped) && (suit == CARD_PTR->suit))
            {
                return true;
            }
        }
        else if (CARD_PTR == 0)
        {
            if (rank == 1)
            {
                return true;
            }
        }
        cout << "Invalid Move" << endl;
        return false;
    }

    // It Print Cards
    void Print()
    {
        if (isFlipped == true)
        {
            if (rank == 1)
            {
                cout << "A" << (isRed ? " Red " : " Black ") << suit << endl;
            }
            else if (rank == 11)
            {
                cout << "K" << (isRed ? " Red " : " Black ") << suit << endl;
            }
            else if (rank == 12)
            {
                cout << "Q" << (isRed ? " Red " : " Black ") << suit << endl;
            }
            else if (rank == 13)
            {
                cout << "J" << (isRed ? " Red " : " Black ") << suit << endl;
            }
            else
            {
                cout << rank << (isRed ? " Red " : " Black ") << suit << endl;
            }
        }
        else
        {
            cout << "[ ]" << endl;
        }
    }

    // It Flip the Card
    void Flip()
    {
        isFlipped = true;
    }

    // It UnFlip the Card
    void UnFlip()
    {
        isFlipped = false;
    }

    // It Checks If Flipped
    bool isFlippedCard()
    {
        return isFlipped;
    }
};

// LinkedList Class
template <class T>
class Linkedlist
{
private:
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;

        // Constructor
        Node(Node *next, Node *prev, T data)
        {
            this->next = next;
            this->prev = prev;
            this->data = data;
        }

        // It return Desire Card
        T *CardChecker()
        {
            return &data;
        }
    };

    Node *head;
    Node *tail;
    int numberOfCards;

public:
    // Constructor
    Linkedlist(const int NUMBER_OF_CARDS = 0)
    {
        if constexpr (is_same<T, Card>::value)
        {
            head = new Node(0, 0, Card());
            tail = new Node(0, head, Card());
        }
        else if constexpr (is_same<T, string>::value)
        {
            head = new Node(0, 0, "\0");
            tail = new Node(0, head, "\0");
        }
        else
        {
            head = new Node(0, 0, 0);
            tail = new Node(0, head, 0);
        }
        head->next = tail;
        numberOfCards = NUMBER_OF_CARDS;
    }

    // Destructor
    ~Linkedlist()
    {
        Node *temp = head->next;
        while (temp != tail)
        {
            temp = temp->next;
            if (temp->prev != 0)
            {
                delete temp->prev;
            }
        }
        delete head;
        delete tail;
    }

    // Iterator Class
    class Iterator
    {
    private:
        Node *current;
        Iterator(Node *current)
        {
            this->current = current;
        }
        friend Linkedlist;

    public:
        // Constructor
        Iterator() : current(0)
        {
        }

        // Operator
        Iterator &operator++()
        {
            current = current->next;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator it = *this;
            current = current->next;
            return it;
        }
        Iterator &operator--()
        {
            current = current->prev;
            return *this;
        }
        Iterator operator--(int)
        {
            Iterator it = *this;
            current = current->prev;
            return it;
        }
        Node *operator*()
        {
            return current;
        }
        bool operator!=(const Iterator &RHS)
        {
            if (current != RHS.current)
            {
                return true;
            }
            return false;
        }
    };

    // Iterator's Related Methods

    // It Point Iterator at the Begining
    Iterator begin()
    {
        return Iterator(head);
    }

    // It Point Iterator at the End
    Iterator end()
    {
        return Iterator(tail);
    }

    // Methods

    // It Insert the Card at the end of the list
    void Insert(T card)
    {
        tail->prev = new Node(tail, tail->prev, card);
        tail->prev->prev->next = tail->prev;
        numberOfCards++;
    }

    // Pop It will Delete Card from the End
    Node *Delete()
    {
        return tail->prev;
    }

    // It Search the Card in the list
    bool isCardFound(const int &RANK, const bool &IS_RED, const string &SUIT)
    {
        Node *temp = head->next;

        while (temp != tail)
        {
            if (temp->data == RANK && temp->data == IS_RED && temp->data == SUIT)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    // Empty Checker
    bool operator!()
    {
        if (head->next == tail && tail->prev == head)
        {
            return true;
        }
        return false;
    }

    // It Check the Winner
    bool isWon()
    {
        if (numberOfCards == 13)
        {
            return true;
        }
        return false;
    }

    // It Return the Latest Card Address
    T *LatestDataChecker()
    {
        if (head->next == tail)
        {
            return 0;
        }
        return &(tail->prev->data);
    }

    // It Push the Old Elements in it
    void Push(Node *ptr)
    {
        Node *temp = ptr;
        Node *temp2 = 0;
        tail->prev->next = ptr;

        while (temp->next != 0)
        {
            temp->data.Flip();
            temp = temp->next;
        }

        temp2 = temp->prev;
        temp->prev = ptr->prev;
        ptr->prev->next = temp;
        tail->prev->next = ptr;
        ptr->prev = tail->prev;
        tail->prev = temp2;
        temp2->next = tail;
        numberOfCards++;
    }

    // It Prints the Detail
    void Print()
    {
        cout << "(" << numberOfCards << " cards)" << endl;

        Node *temp = head->next;
        while (temp != tail)
        {
            temp->data.Print();
            temp = temp->next;
        }
    }

    // It Decrements Card Count
    void NumbersDec()
    {
        numberOfCards--;
    }

    // It Permenantly Delete the Node
    void Pop()
    {
        Node *temp = tail->prev;
        tail->prev->prev->next = tail;
        tail->prev = tail->prev->prev;
        delete temp;
    }

    // It Adjust the Condition of Card
    void ConditionAdjuster(Stack<bool> &stack)
    {
        Iterator it;
        it = end();
        it--;
        if (((*(stack.IteratorGiver()))->data) == true)
        {
            (*it)->data.Flip();
        }
        else
        {
            (*it)->data.UnFlip();
        }
    }
};

// Stack Class
template <class U>
class Stack
{
private:
    Linkedlist<U> stack;

public:
    // Methods

    // It push Data on Stack
    void Push(U data)
    {
        stack.Insert(data);
    }

    // It Pop Data From Stack
    void Pop()
    {
        stack.Delete();
    }

    // It Search Card in Stack
    bool isCardFound(const int &RANK, const bool &IS_RED, const string &SUIT)
    {
        return stack.isCardFound(RANK, IS_RED, SUIT);
    }

    // Empty Checker
    bool operator!()
    {
        return !stack;
    }

    // It Gives the Latest Card in Stack
    U *LatestDataChecker()
    {
        if (!stack)
        {
            return 0;
        }
        else
        {
            return stack.LatestDataChecker();
        }
    }

    // It Prints the Detail
    void Print()
    {
        stack.Print();
    }

    // It Check if Player Won
    bool isWon()
    {
        return stack.isWon();
    }

    // It Push the Exiting Card
    void Insert(typename Linkedlist<U>::Iterator it)
    {
        stack.Push(*it);
    }

    // It gives the Iterator Pointing to Last Address
    typename Linkedlist<U>::Iterator IteratorGiver()
    {
        typename Linkedlist<U>::Iterator it;
        it = stack.end();
        it--;
        return it;
    }

    // It Decrements Cards Number
    void NumbersDec()
    {
        stack.NumbersDec();
    }

    // It Permenantly Delete Node
    void Delete()
    {
        stack.Pop();
    }
};

// Game Class
class Game
{
private:
    Linkedlist<Card> C1;
    Linkedlist<Card> C2;
    Linkedlist<Card> C3;
    Linkedlist<Card> C4;
    Linkedlist<Card> C5;
    Linkedlist<Card> C6;
    Linkedlist<Card> C7;

    Stack<Card> stock;
    Stack<Card> wastePile;
    Stack<Card> foundation1;
    Stack<Card> foundation2;
    Stack<Card> foundation3;
    Stack<Card> foundation4;

    // Undo List
    Stack<string> undoSource;
    Stack<string> undoDestination;
    Stack<int> undoNumber;
    Stack<bool> isUpperFlipped;

    // System's Methods

    // It Generates Color Randomly
    bool ColorGenerator()
    {
        return rand() % 2;
    }

    // It Generates Card Number Randomly
    int CardGenerator()
    {
        return ((rand() % 12) + 1);
    }

    // It Generates the Suit Randomly
    string SuitGenerator()
    {
        int temp = 0;
        temp = rand() % 4;

        if (temp == 0)
        {
            return "\u2665";
        }
        else if (temp == 1)
        {
            return "\u2666";
        }
        else if (temp == 2)
        {
            return "\u2660";
        }
        else
        {
            return "\u2663";
        }
    }

    // It Randomly Distribute Cards
    void RandomDistributer()
    {
        int rank = 0;
        bool isRed = false;
        string suit;
        int i = 0;

        while (i < 52)
        {
            rank = CardGenerator();
            isRed = ColorGenerator();
            suit = SuitGenerator();

            if ((!C1.isCardFound(rank, isRed, suit)) && (!C2.isCardFound(rank, isRed, suit)) && (!C3.isCardFound(rank, isRed, suit)) &&
                (!C4.isCardFound(rank, isRed, suit)) && (!C5.isCardFound(rank, isRed, suit)) && (!C6.isCardFound(rank, isRed, suit)) &&
                (!C7.isCardFound(rank, isRed, suit)) && (!stock.isCardFound(rank, isRed, suit)))
            {
                if (i < 1)
                {
                    C1.Insert(Card(11, isRed, suit));
                }
                else if (i < 3)
                {
                    C2.Insert(Card(rank, isRed, suit));
                }
                else if (i < 6)
                {
                    C3.Insert(Card(rank, isRed, suit));
                }
                else if (i < 10)
                {
                    C4.Insert(Card(rank, isRed, suit));
                }
                else if (i < 15)
                {
                    C5.Insert(Card(rank, isRed, suit));
                }
                else if (i < 21)
                {
                    C6.Insert(Card(rank, isRed, suit));
                }
                else if (i < 28)
                {
                    C7.Insert(Card(rank, isRed, suit));
                }
                else
                {
                    stock.Push(Card(rank, isRed, suit));
                }
                i++;
            }
        }
        Linkedlist<Card>::Iterator it;
        it = C1.end();
        it--;
        (*it)->data.Flip();

        it = C2.end();
        it--;
        (*it)->data.Flip();

        it = C3.end();
        it--;
        (*it)->data.Flip();

        it = C4.end();
        it--;
        (*it)->data.Flip();

        it = C5.end();
        it--;
        (*it)->data.Flip();

        it = C6.end();
        it--;
        (*it)->data.Flip();

        it = C7.end();
        it--;
        (*it)->data.Flip();
    }

public:
    // Constructor
    Game()
    {
        RandomDistributer();
    }

    // It Prints the Detail
    void Print()
    {

        cout << "\n\n---------=> Stock <=--------\n\n"
             << endl;
        stock.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n---------=> Waste <=--------\n\n"
             << endl;
        wastePile.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n------=> Foundation1 <=-----\n\n"
             << endl;
        foundation1.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n------=> Foundation2 <=-----\n\n"
             << endl;
        foundation2.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n------=> Foundation3 <=-----\n\n"
             << endl;
        foundation3.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n------=> Foundation4 <=-----\n\n"
             << endl;
        foundation4.Print();
        cout << "\n\n----------------------------\n\n";
        cout << endl;
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "\n\n--------=> Column1 <=-------\n\n"
             << endl;
        C1.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column2 <=-------\n\n"
             << endl;
        C2.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column3 <=-------\n\n"
             << endl;
        C3.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column4 <=-------\n\n"
             << endl;
        C4.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column5 <=-------\n\n"
             << endl;
        C5.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column6 <=-------\n\n"
             << endl;
        C6.Print();
        cout << "\n\n----------------------------\n\n";
        cout << "\n\n--------=> Column7 <=-------\n\n"
             << endl;
        C7.Print();
        cout << "\n\n----------------------------\n\n";
    }

    // It Check if the Player Won
    bool isWon()
    {
        if (foundation1.isWon() && foundation2.isWon() && foundation3.isWon() && foundation4.isWon())
        {
            cout << "\n\n--------=> Result <=--------\n\n"
                 << endl;
            cout << "You Won " << endl;
            cout << "\n\n----------------------------\n\n";
            return true;
        }
        return false;
    }

    // It Execute Command
    void CommandExecuter(int command, string destination, string source, int number = 0)
    {
        bool isValid = false;

        if (command == 'z')
        {
            Linkedlist<string>::Iterator it1;
            Linkedlist<int>::Iterator it2;
            if (!(!undoDestination))
            {
                it1 = undoDestination.IteratorGiver();
                source = *(undoDestination.LatestDataChecker());
                undoDestination.Delete();
            }
            else{
                return;
            }
            if (!(!undoSource))
            {
                it1 = undoSource.IteratorGiver();
                destination = *(undoSource.LatestDataChecker());
                undoSource.Delete();
            }
            else
            {
                return;
            }
            if (!(!undoNumber))
            {
                it2 = undoNumber.IteratorGiver();
                number = *(undoNumber.LatestDataChecker());
                undoNumber.Delete();
            }
            else
            {
            return;
            }
            UndoCommandExecuter(destination, source, number);
            return;
        }

        if (destination != "\0" || source != "\0")
        {
            Linkedlist<Card>::Iterator it;
            Card card;
            int i = 0;
            if (source == "C1")
            {
                it = C1.end();

                while (i < number && it != C1.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());

                if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C1.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C1.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C1.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C1.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C1.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C1.end();
                    --it;
                    if (it != C1.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C2")
            {
                it = C2.end();
                while (i < number && it != C2.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());
                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C2.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C2.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C2.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C2.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C2.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C2.end();
                    --it;
                    if (it != C2.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C3")
            {
                it = C3.end();
                while (i < number && it != C3.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());

                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C3.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C3.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C3.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C3.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C3.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C3.end();
                    --it;
                    if (it != C3.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C4")
            {
                it = C4.end();
                while (i < number && it != C4.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());

                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C4.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C4.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C4.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C4.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C4.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C4.end();
                    --it;
                    if (it != C4.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C5")
            {
                it = C5.end();
                while (i < number && it != C5.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());

                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C5.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C5.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C5.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C5.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C5.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C5.end();
                    --it;
                    if (it != C5.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C6")
            {
                it = C6.end();
                while (i < number && it != C6.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());
                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    C6.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C6.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C6.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C6.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C6.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C6.end();
                    --it;

                    if (it != C6.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "C7")
            {
                it = C7.end();
                while (i < number && it != C7.begin())
                {
                    it--;
                    i++;
                }
                card = *((*it)->CardChecker());
                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    C7.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        C7.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        C7.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        C7.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        C7.NumbersDec();
                        isValid = true;
                    }
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
                if (isValid == true)
                {
                    it = C7.end();
                    --it;
                    if (it != C7.begin())
                    {
                        isUpperFlipped.Push((*it)->data.isFlippedCard());
                        ((*it)->data).Flip();
                    }
                }
            }
            else if (source == "S")
            {
                if (!stock)
                {
                    while (!(!wastePile))
                    {
                        it = wastePile.IteratorGiver();
                        (*it)->data.UnFlip();
                        stock.Insert(it);
                        wastePile.NumbersDec();
                        ;
                    }
                }
                else
                {
                    wastePile.Insert(stock.IteratorGiver());
                    stock.NumbersDec();
                    isValid = true;
                }
            }
            else if (source == "W")
            {
                it = wastePile.IteratorGiver();
                card = *((*it)->CardChecker());

                if (destination == "C1" && (card.ToColChecker(C1.LatestDataChecker())))
                {
                    C1.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C2" && (card.ToColChecker(C2.LatestDataChecker())))
                {
                    C2.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C3" && (card.ToColChecker(C3.LatestDataChecker())))
                {
                    C3.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C4" && (card.ToColChecker(C4.LatestDataChecker())))
                {
                    C4.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C5" && (card.ToColChecker(C5.LatestDataChecker())))
                {
                    C5.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C6" && (card.ToColChecker(C6.LatestDataChecker())))
                {
                    C6.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "C7" && (card.ToColChecker(C7.LatestDataChecker())))
                {
                    C7.Push(*it);
                    wastePile.NumbersDec();
                    isValid = true;
                }
                else if (destination == "F1")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation1.LatestDataChecker()))
                    {
                        foundation1.Insert(it);
                        wastePile.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F2")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation2.LatestDataChecker()))
                    {
                        foundation2.Insert(it);
                        wastePile.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F3")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation3.LatestDataChecker()))
                    {
                        foundation3.Insert(it);
                        wastePile.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "F4")
                {
                    if (number == 1 && card.ToFoundationChecker(foundation4.LatestDataChecker()))
                    {
                        foundation4.Insert(it);
                        wastePile.NumbersDec();
                        isValid = true;
                    }
                }
                else if (destination == "S")
                {
                    it = wastePile.IteratorGiver();
                    stock.Insert(it);
                    (*it)->data.UnFlip();
                    wastePile.NumbersDec();
                }
                else
                {
                    cout << "Invalid Move" << endl;
                }
            }
            if (command != 'z')
            {
                if (isValid == true)
                {
                    undoDestination.Push(destination);
                    undoSource.Push(source);
                    undoNumber.Push(number);
                }
            }
        }
    }

    // It Will Execute Undo Commands
    void UndoCommandExecuter(string destination, string source, int number = 0)
    {
        if (destination != "\0" || source != "\0")
        {
            Linkedlist<Card>::Iterator it;
            Linkedlist<Card>::Iterator it2;
            int i = 0;

            if (source == "C1")
            {
                it = C1.end();

                while (i < number && it != C1.begin())
                {
                    it--;
                    i++;
                }
                if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C1.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C1.NumbersDec();
                }
            }
            else if (source == "C2")
            {
                it = C2.end();
                while (i < number && it != C2.begin())
                {
                    it--;
                    i++;
                }
                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C2.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C2.NumbersDec();
                }
            }
            else if (source == "C3")
            {
                it = C3.end();
                while (i < number && it != C3.begin())
                {
                    it--;
                    i++;
                }

                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C3.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C3.NumbersDec();
                }
            }
            else if (source == "C4")
            {
                it = C4.end();
                while (i < number && it != C4.begin())
                {
                    it--;
                    i++;
                }

                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C4.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C4.NumbersDec();
                }
            }
            else if (source == "C5")
            {
                it = C5.end();
                while (i < number && it != C5.begin())
                {
                    it--;
                    i++;
                }
                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C5.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C5.NumbersDec();
                }
            }
            else if (source == "C6")
            {
                it = C6.end();
                while (i < number && it != C6.begin())
                {
                    it--;
                    i++;
                }
                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    C6.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C6.NumbersDec();
                }
            }
            else if (source == "C7")
            {
                it = C7.end();
                while (i < number && it != C7.begin())
                {
                    it--;
                    i++;
                }
                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    C7.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    C7.NumbersDec();
                }
            }
            else if (source == "W")
            {
                it = wastePile.IteratorGiver();
                if (destination == "S")
                {
                    stock.Insert(it);
                    (*it)->data.UnFlip();
                    wastePile.NumbersDec();
                }
            }
            else if (source == "F1")
            {
                it = foundation1.IteratorGiver();
                it++;
                while (i < number)
                {
                    it--;
                    i++;
                }
                if (destination == "C1")
                {
                    C1.ConditionAdjuster(isUpperFlipped);
                    C1.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C2")
                {
                    C2.ConditionAdjuster(isUpperFlipped);
                    C2.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C3")
                {
                    C3.ConditionAdjuster(isUpperFlipped);
                    C3.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C4")
                {
                    C4.ConditionAdjuster(isUpperFlipped);
                    C4.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C5")
                {
                    C5.ConditionAdjuster(isUpperFlipped);
                    C5.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C6")
                {
                    C6.ConditionAdjuster(isUpperFlipped);
                    C6.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "C7")
                {
                    C7.ConditionAdjuster(isUpperFlipped);
                    C7.Push(*it);
                    foundation1.NumbersDec();
                }
                else if (destination == "W")
                {
                    wastePile.Insert(it);
                    foundation1.NumbersDec();
                }
                else if (source == "F2")
                {
                    it = foundation2.IteratorGiver();
                    it++;
                    while (i < number)
                    {
                        it--;
                        i++;
                    }
                    if (destination == "C1")
                    {
                        C1.ConditionAdjuster(isUpperFlipped);
                        C1.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C2")
                    {
                        C2.ConditionAdjuster(isUpperFlipped);
                        C2.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C3")
                    {
                        C3.ConditionAdjuster(isUpperFlipped);
                        C3.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C4")
                    {
                        C4.ConditionAdjuster(isUpperFlipped);
                        C4.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C5")
                    {
                        C5.ConditionAdjuster(isUpperFlipped);
                        C5.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C6")
                    {
                        C6.ConditionAdjuster(isUpperFlipped);
                        C6.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "C7")
                    {
                        C7.ConditionAdjuster(isUpperFlipped);
                        C7.Push(*it);
                        foundation2.NumbersDec();
                    }
                    else if (destination == "W")
                    {
                        wastePile.Insert(it);
                        foundation2.NumbersDec();
                    }
                }
                else if (source == "F3")
                {
                    it = foundation3.IteratorGiver();
                    it++;
                    while (i < number)
                    {
                        it--;
                        i++;
                    }
                    if (destination == "C1")
                    {
                        C1.ConditionAdjuster(isUpperFlipped);
                        C1.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C2")
                    {
                        C2.ConditionAdjuster(isUpperFlipped);
                        C2.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C3")
                    {
                        C3.ConditionAdjuster(isUpperFlipped);
                        C3.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C4")
                    {
                        C4.ConditionAdjuster(isUpperFlipped);
                        C4.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C5")
                    {
                        C5.ConditionAdjuster(isUpperFlipped);
                        C5.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C6")
                    {
                        C6.ConditionAdjuster(isUpperFlipped);
                        C6.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "C7")
                    {
                        C7.ConditionAdjuster(isUpperFlipped);
                        C7.Push(*it);
                        foundation3.NumbersDec();
                    }
                    else if (destination == "W")
                    {
                        wastePile.Insert(it);
                        foundation3.NumbersDec();
                    }
                }
                else if (source == "F4")
                {
                    it = foundation4.IteratorGiver();
                    it++;
                    while (i < number)
                    {
                        it--;
                        i++;
                    }
                    if (destination == "C1")
                    {
                        C1.ConditionAdjuster(isUpperFlipped);
                        C1.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C2")
                    {
                        C2.ConditionAdjuster(isUpperFlipped);
                        C2.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C3")
                    {
                        C3.ConditionAdjuster(isUpperFlipped);
                        C3.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C4")
                    {
                        C4.ConditionAdjuster(isUpperFlipped);
                        C4.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C5")
                    {
                        C5.ConditionAdjuster(isUpperFlipped);
                        C5.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C6")
                    {
                        C6.ConditionAdjuster(isUpperFlipped);
                        C6.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "C7")
                    {
                        C7.ConditionAdjuster(isUpperFlipped);
                        C7.Push(*it);
                        foundation4.NumbersDec();
                    }
                    else if (destination == "W")
                    {
                        wastePile.Insert(it);
                        foundation4.NumbersDec();
                    }
                }
            }
        }
    }
};

// Command Class
class Command
{
private:
    char command;
    string destination;
    string source;
    int number;
    Game g;

public:
    // Constructor
    Command() : command('\0'), number(0)
    {
    }

    // It Print Interface
    void Input()
    {
        cout << "Enter Function You Want to Perform: ";
        cin >> command;
        cin.ignore();
        if (command != 'z')
        {
            cout << "Enter the Source for the Pickup of Card: ";
            cin >> source;
            cin.ignore();
            if (source != "S")
            {
                cout << "Enter the Destination for the Placement of Card: ";
                cin >> destination;
                cin.ignore();
                if (destination != "F1" && destination != "F2" && destination != "F3" && destination != "F4")
                {
                    cout << "Enter the Number of Cards you want to Move: ";
                    cin >> number;
                }
                else
                {
                    number = 1;
                }
            }
            else
            {
                destination = 'W';
                number = 1;
            }
        }
        CommandExecuter();
    }

    // Command Executer
    void CommandExecuter()
    {
        g.CommandExecuter(command, destination, source, number);
    }

    // It Control the Game
    void Controller()
    {
        while (!(g.isWon()))
        {
            g.Print();
            Input();
        }
    }
};

int main()
{
    srand(time(0));
    Command c;
    c.Controller();
    return 0;
}