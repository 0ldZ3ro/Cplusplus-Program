/*
 * Project 3: Corner Grocer
 * CS 210: Programming Languages
 *
 * Date: [6/20/2021]
 * Author: [Javier Ortiz Jr]
 * Professor: [Bill Chan]
 */
// Alot of help with this one on other sites. 
#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functinon you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
// display for program
void displayMenu() {
	cout << "1: Items Purchased List " << endl;
	cout << "2: Search for quantity of specific item " << endl;
	cout << "3: Histogram of items and quantities" << endl;
	cout << "4: Quit" << endl;
	cout << "Enter your selection as a number 1, 2, 3, or 4." << endl;
}

// main program
int main()
{

	// loop for menu and cases
	while (true) {

		displayMenu();

		int userInput;
		string item;
		int itemFreq;
		cin >> userInput;

		// if the input is not the correct variable type
		if (!cin) {

			system("CLS");
			system("Color 0C");
			cout << "Invalid entry, please try again." << endl;

			// cin.clear and cin.ignore with numeric value to exit error loop when not integer
			cin.clear();
			cin.ignore(10000, '\n');

			// sleep to delay error message then clear screen
			Sleep(4000);
			system("CLS");
			system("Color 02");


			continue;
		}

		// Menu cases 
		switch (userInput) {


			// Calls to purchase list funtion in python 
		case 1:

			
			// clears screen to clean it up
			system("CLS");
			
			system("Color 03");
			cout << endl;

			// call to purchase list 
			CallProcedure("purchaseList");
			cout << endl;
			cout << endl;
			break;



			// calls to function to search for a certain quantity of an item 
		case 2:


			// clears screen to clean it up
			system("CLS");
			system("Color 0D");
			// request for user input to check for item quantity purchased
			cout << "Enter Item for quantity purchased: ";
			cin >> item;
			cout << endl;

			// call to frequency of item function
			itemFreq = callIntFunc("freqItem", item);
			// if statement number returned is 0 or less than user is informed 
			if (itemFreq < 1) {
				cout << "That Item was not purchased today. Make sure correct item is input." << endl;
			}
			else {
				cout << itemFreq << "- " << item << " purchased today" << endl;
			}
			cout << endl;
			cout << endl;
			break;

		case 3:

			system("CLS");
			system("Color 06");
			CallProcedure("Histogram");

			cout << endl;
			cout << endl;

			break;

			// exits
		case 4:
			system("CLS");
			system("Color 09");
			
			cout << "Thank you for using the program, now exiting.";

			// delays prgram to see message before exiting
			Sleep(3000);
			exit(1);

			break;

			// error case
		default:
			system("CLS");
			system("Color 04");
		
			cout << "Error: Invalid choice entered, please try again.\n";
			// delay for error message to display before break
			Sleep(4000);
			system("CLS");
			system("Color 02");

			break;
		}

		// Code Commented out because it is unnecessary for now. 
		// CallProcedure("printsomething");
		// cout << callIntFunc("PrintMe", "House") << endl;
		// cout << callIntFunc("SquareValue", 2);
	}
}