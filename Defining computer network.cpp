// Pauls Brikmanis 5.grupa 201RDB002
// 7.variants 2.Laboratorijas darbs
#include <iostream>
#include <typeinfo>
using namespace std;

class OverflowException
{
public:
	OverflowException()
	{
		cout << endl
			 << "Exception created!" << endl;
	}
	OverflowException(const OverflowException &)
	{
		cout << "Exception copied!" << endl;
	}
	~OverflowException()
	{
		cout << "Exception finished!" << endl;
	}
};

template <class T>
class Computer
{
protected:
	string procesors;
	float frekvence;
	T operativas_atminas_apjoms;

public:
	Computer();
	Computer(string, float, T);

	virtual ~Computer()
	{
		cout << "Message from the \"Computer\" - destroyed!" << endl;
	}

	virtual void Print() const;

	string Get_procesors() const;
	float Get_frekvence() const;
	T Get_operativas_atminas_apjoms() const;

	void Set_procesors(string);
	void Set_frekvence(float);
	void Set_operativas_atminas_apjoms(T);
};

template <class T>
class NetComputer : public Computer<T>
{
private:
	string IP_adrese;

public:
	NetComputer() : Computer<T>(), IP_adrese()
	{
	}
	NetComputer(string, float, T, string);
	virtual ~NetComputer()
	{
		cout << endl
			 << "Message from the \"NetComputer\" - destroyed!" << endl;
	}
	string GetIP_adrese() const
	{
		return IP_adrese;
	}
	void SetIP_adrese(string IP_adrese)
	{
		this->IP_adrese = IP_adrese;
	}
	virtual void Print() const;
};

template <class T>
class ComputerNetwork
{
private:
	typedef NetComputer<T> *NCPointer;
	NCPointer *Nodes;
	static const unsigned int DEFAULT_MAX_LENGTH = 5;
	unsigned int MaxLength;
	unsigned int Ram;	   // Lenght nomainīju uz Ram
	unsigned short MaxRam; // Te kjip bija usnigned int LineColor un viņš teica, ka jāņem nost, es nez, ko likt, ieliku šo
public:
	ComputerNetwork() : MaxLength(DEFAULT_MAX_LENGTH), Ram(0), MaxRam(0)
	{
		Nodes = new NCPointer[MaxLength];
	}
	ComputerNetwork(unsigned int MaxLength, unsigned short MaxRam) : MaxLength(MaxLength), Ram(0)
	{
		this->MaxRam = MaxRam; // Ganjau te dirsā
		Nodes = new NCPointer[MaxLength];
	}
	~ComputerNetwork();
	static unsigned int GetDefaultMaxRam()
	{
		return DEFAULT_MAX_LENGTH;
	}
	int GetRam() const
	{
		return Ram;
	}
	void AddNode(const NetComputer<T> &);
	void Print() const;
	T GetMaxRam();
};

template <class T>
Computer<T>::Computer() : procesors(""), frekvence(0.0), operativas_atminas_apjoms(0) {}

template <class T>
Computer<T>::Computer(string a, float b, T c)
{
	procesors = a;
	frekvence = b;
	operativas_atminas_apjoms = c;
}

template <class T>
inline void Computer<T>::Print() const
{
	cout << "procesors = " << procesors << endl;
	cout << "frekvence = " << frekvence << endl;
	cout << "operativas_atminas_apjoms = " << operativas_atminas_apjoms << endl;
}

template <class T>
inline string Computer<T>::Get_procesors() const
{
	return procesors;
}

template <class T>
inline float Computer<T>::Get_frekvence() const
{
	return frekvence;
}

template <class T>
inline T Computer<T>::Get_operativas_atminas_apjoms() const
{
	return operativas_atminas_apjoms;
}

template <class T>
inline void Computer<T>::Set_procesors(string t)
{
	this->procesors = t;
}

template <class T>
inline void Computer<T>::Set_frekvence(float t)
{
	this->frekvence = t;
}

template <class T>
inline void Computer<T>::Set_operativas_atminas_apjoms(T t)
{
	this->operativas_atminas_apjoms = t;
}

template <class T>
NetComputer<T>::NetComputer(string a, float b, T c, string IP_adreseZ) : Computer<T>(a, b, c)
{
	IP_adrese = IP_adreseZ;
}

template <class T>
inline void NetComputer<T>::Print() const
{
	Computer<T>::Print();
	cout << ", IP_adrese = " << IP_adrese;
}

template <class T>
ComputerNetwork<T>::~ComputerNetwork()
{
	for (unsigned int i = 0; i < Ram; i++)
		delete Nodes[i];
	delete[] Nodes;
}

template <class T>
void ComputerNetwork<T>::Print() const
{
	cout << "\nMax Ram ir: " << MaxRam << "." << endl // šeit linecolor vietā arī ieliku
		 << "Line's nodes:" << endl;
	for (unsigned int i = 0; i < Ram; i++)
	{
		cout << (i + 1) << ". ";
		Nodes[i]->Print();
		cout << "." << endl;
	}
}

template <class T>
void ComputerNetwork<T>::AddNode(const NetComputer<T> &Node)
{
	if (Ram == MaxRam)
		throw OverflowException();
	else
		Nodes[Ram++] = new NetComputer<T>(
			Node.Get_procesors(), Node.Get_frekvence(), Node.Get_operativas_atminas_apjoms(), Node.GetIP_adrese());
}

template <class T>
T ComputerNetwork<T>::GetMaxRam()
{
	T maxRam = Nodes[0]->Get_operativas_atminas_apjoms();
	for (int i = 1; i < Ram; i++)
	{
		if (Nodes[i]->Get_operativas_atminas_apjoms() > maxRam)
		{
			maxRam = Nodes[i]->Get_operativas_atminas_apjoms();
		}
	}
	return maxRam;
}

int main(void)
{
	ComputerNetwork<unsigned int> *IntLine = new ComputerNetwork<unsigned int>(2, 1);
	ComputerNetwork<unsigned short> *ShortLine = new ComputerNetwork<unsigned short>(2, 1);

	NetComputer<unsigned int> *IntD1 = new NetComputer<unsigned int>("string1", 1.1, 1, "string1");
	NetComputer<unsigned short> *ShortD1 = new NetComputer<unsigned short>("string2", 2.2, 2, "string2");

	NetComputer<unsigned int> IntD2("string3", 3.3, 3, "string3");
	NetComputer<unsigned short> ShortD2("string4", 4.4, 4, "string4");

	try
	{
		IntLine->AddNode(*IntD1);
		cout << "\nNew INT node has been added successfully!" << endl;
	}
	catch (OverflowException &)
	{
		cout << "Error: maximal size exceeded!" << endl;
	}
	catch (...)
	{
		cout << "Unknown Error!" << endl;
	}

	try
	{
		IntLine->AddNode(IntD2);
		cout << "\nNew INT node has been added successfully!" << endl;
	}
	catch (OverflowException &)
	{
		cout << "Error: maximal size exceeded!" << endl;
	}
	catch (...)
	{
		cout << "Unknown Error!" << endl;
	}

	try
	{
		ShortLine->AddNode(*ShortD1);
		cout << "\nNew Short node has been added successfully!" << endl;
	}
	catch (OverflowException &)
	{
		cout << "Error: maximal size exceeded!" << endl;
	}
	catch (...)
	{
		cout << "Unknown Error!" << endl;
	}

	try
	{
		ShortLine->AddNode(ShortD2);
		cout << "\nNew Short node has been added successfully!" << endl;
	}
	catch (OverflowException &)
	{
		cout << "Error: maximal size exceeded!" << endl;
	}
	catch (...)
	{
		cout << "Unknown Error!" << endl;
	}

	delete IntD1;
	delete ShortD1;

	cout << endl
		 << "INT line:";
	IntLine->Print();

	cout << endl
		 << "Short line:";
	ShortLine->Print();

	delete IntLine;
	delete ShortLine;

	cin.get();
	return 0;
}