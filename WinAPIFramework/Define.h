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
#define TIMER						GET_SINGLE(TimerManager)
#define INPUT						GET_SINGLE(InputManager)
#define TIME						GET_SINGLE(TimeManager)

#define CORE_DESC					CORE.GetDesc()
#define CUR_HWND					CORE.GetDesc().hWnd

#define CUR_DEMO(demoName)		static_pointer_cast<demoName>(CORE_DESC.app)
#define CUR_DEMO_DESC(demoName) static_pointer_cast<demoName>(CORE_DESC.app)>GetAppDesc()
#define CUR_SCREEN_CENTER		POINT{(LONG)CORE.GetWindowSize().width / 2, (LONG)CORE.GetWindowSize().height / 2}

// Utils

#define _SHAPES_BEGIN         \
    namespace shapes {		 


#define _SHAPES_END \
    }			  
