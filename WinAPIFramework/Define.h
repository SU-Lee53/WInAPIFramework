#pragma once

#define DECLARE_SINGLE(classname)			\
private:									\
	classname() { }							\
public:										\
	static classname& GetInstance()			\
	{										\
		static classname s_instance;		\
		return s_instance;					\
	}


#define GET_SINGLE(classname)	classname::GetInstance()

#define CORE						GET_SINGLE(Core)
#define RANDOM						GET_SINGLE(RandomGenerator)
#define CARET						GET_SINGLE(Caret)


#define CORE_DESC					CORE.GetDesc()
#define CUR_HWND					CORE.GetDesc().hWnd

#define CUR_DEMO(demoName)		static_pointer_cast<demoName>(CORE_DESC.app)

// Utils
