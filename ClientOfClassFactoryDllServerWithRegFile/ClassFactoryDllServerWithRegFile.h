class ISum :public IUnknown
{
public:
	//ISum specific method declaration
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int *) = 0;//pure virtual
};

class ISubtract :public IUnknown
{
public:
	//ISubtract specific method declaration
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;//pure virtual
};

//CLSID of SumSubtract Component {855DA3FB-47EB-4C49-AE55-3C9AC1BCB28B}
const CLSID CLSID_SumSubtract =
{ 0x855da3fb, 0x47eb, 0x4c49, 0xae, 0x55, 0x3c, 0x9a, 0xc1, 0xbc, 0xb2, 0x8b };

//IID of ISum Interface {A3FC4EB3-5DBB-44BD-8496-4A93CB3910DC}
const IID IID_ISum =
{ 0xa3fc4eb3, 0x5dbb, 0x44bd, 0x84, 0x96, 0x4a, 0x93, 0xcb, 0x39, 0x10, 0xdc };

//IID of ISubtract Interface {3942876D-71F8-4DC3-ACB2-86A63FF2123A}
const IID IID_ISubtract =
{ 0x3942876d, 0x71f8, 0x4dc3, 0xac, 0xb2, 0x86, 0xa6, 0x3f, 0xf2, 0x12, 0x3a };

