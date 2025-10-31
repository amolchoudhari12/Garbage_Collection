// This is the main project file for VC++ application project 
// generated using an Application Wizard.
//
// Written by Chris Maunder (chris@codeproject.com)
// The Code Project, http://www.codeproject.com


#include "stdafx.h"

#using <mscorlib.dll>

using namespace System;

__gc class MyGCClass
{
	int n;
};

__gc class CFinalizeTest : public Object, public IDisposable
{
public:
	CFinalizeTest()  
	{
		Console::WriteLine("In CFinalizeTest::CFinalizeTest()"); 
		m_bDisposed = false;
	}

	virtual ~CFinalizeTest() 
	{
		Console::WriteLine("In CFinalizeTest::~CFinalizeTest()"); 
		Dispose();
	}

public:
	// You are encouraged to not allow a disposed object to be reused
	void MyMethod()
	{
       if (!m_bDisposed)
	   {
		   // do something
	   }
	   else
	   {
		   // throw an exception
	   }
	}

	// Cleanup code - either call Close directly, or 
public:
	void Close() 
	{
		Console::WriteLine("In CFinalizeTest::Close() - releasing resources"); 
		Dispose();
	}

	void Dispose()
	{
		if (!m_bDisposed)
		{
			m_bDisposed = true;
			Console::WriteLine("In CFinalizeTest::Dispose()"); 

			Console::WriteLine("Freeing resources..."); 

			GC::SuppressFinalize(this);  
		}
	}

protected:
	bool m_bDisposed;
};

// This is the entry point for this application
#ifdef _UNICODE
int wmain(void)
#else
int main(void)
#endif
{
	Console::WriteLine("Garbage Collection demonstration\n");

	__int64 TotalMem = GC::GetTotalMemory(true);
	Console::WriteLine("Currently used {0} bytes of memory", TotalMem.ToString());

	// Wanton disregard for all the things we've been taught
	Console::WriteLine("Creating a ton of junk");
	for (int i = 0; i < 10000; i++)
		new MyGCClass();

	TotalMem = GC::GetTotalMemory(false);
	Console::WriteLine("Have now used {0} bytes of memory", TotalMem.ToString());

	GC::Collect();

	TotalMem = GC::GetTotalMemory(false);
	Console::WriteLine("After GC, used {0} bytes of memory", TotalMem.ToString());

	// -------------------------------------------------------------
	// Demonstration of Generations...

	Console::WriteLine("\nDemonstration of Generations\n");

	String* str = new String("This is a string");
	Console::WriteLine("We have created the string '{0}'", str);

	// How old is it?
	int nMaxGen = GC::MaxGeneration;
	int nGen = GC::GetGeneration(str);
	Console::WriteLine("The object's generation is '{0} (max {0})'", 
		nGen.ToString(), nMaxGen.ToString());

	// Let's make it older and wiser
	Console::WriteLine("Garbage Collecting...");
	GC::Collect();
	nGen = GC::GetGeneration(str);
	Console::WriteLine("The object's generation is '{0} (max {0})'", 
		nGen.ToString(), nMaxGen.ToString());

	Console::WriteLine("Garbage Collecting...");
	GC::Collect();
	nGen = GC::GetGeneration(str);
	Console::WriteLine("The object's generation is '{0} (max {0})'", 
		nGen.ToString(), nMaxGen.ToString());

	Console::WriteLine("Garbage Collecting...");
	GC::Collect();
	nGen = GC::GetGeneration(str);
	Console::WriteLine("The object's generation is '{0} (max {0})'", 
		nGen.ToString(), nMaxGen.ToString());

	// -------------------------------------------------------------
	// Demonstration of Weak References...

	Console::WriteLine("\nDemonstration of Weak References\n");

	Console::WriteLine("Creating a weak reference.");
	WeakReference* weak = new WeakReference(str);
	str = 0;

	if (weak->IsAlive)
	{
		str = __try_cast<String*> (weak->Target);
		Console::WriteLine("Object is alive. [{0}]", str);
		str = 0;
	}
	else
		Console::WriteLine("Object is gone");

	GC::Collect(0);

	if (weak->IsAlive)
	{
		str = __try_cast<String*> (weak->Target);
		Console::WriteLine("Object survived GC of generation 0. [{0}]", str);
		str = 0;
	}
	else
		Console::WriteLine("Object is gone (collected with Gen 0)");


	GC::Collect(1);

	if (weak->IsAlive)
	{
		str = __try_cast<String*> (weak->Target);
		Console::WriteLine("Object survived GC of generation 1. [{0}]", str);
		str = 0;
	}
	else
		Console::WriteLine("Object is gone (collected with Gen 1)");


	GC::Collect(2);

	if (weak->IsAlive)
	{
		str = __try_cast<String*> (weak->Target);
		Console::WriteLine("Object survived GC of generation 2. [{0}]", str);
		str = 0;
	}
	else
		Console::WriteLine("Object is gone (collected with Gen 2)");

	// -------------------------------------------------------------
	// Demonstration of Finalize/Dispose...

	Console::WriteLine("\nDemonstration of Finalize/Dispose\n");


	Console::WriteLine("Creating a CFinalizeTest object.");
	CFinalizeTest* ft = new CFinalizeTest();
	Console::WriteLine("Calling 'Close' then allowing the GC to collect it.");
	ft->Close(); // or ft.Dispose() if you want
	ft = 0;
	GC::Collect();

	Console::WriteLine("Creating a CFinalizeTest object, and will now delete it");
	ft = new CFinalizeTest();
	delete ft;
	ft = 0;


	Console::WriteLine("Creating a CFinalizeTest object, no Close or release to the GC.");
	ft = new CFinalizeTest();

	Console::WriteLine(" -- PROGRAM ENDS --\nPress Enter to continue");
	Console::ReadLine();

	return 0;

}