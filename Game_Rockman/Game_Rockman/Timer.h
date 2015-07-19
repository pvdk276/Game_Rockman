#pragma once
#include <Windows.h>
#include "Global.h"

/*C+==================================================================
Class:    CTimer

Summary:  Lớp CTimer gồm các thuộc tính và phương thức tính toán
và xử lý thời gian trong vòng lặp game cũng như trong
các hàm Update của các đối tượng game
==================================================================-C*/

class CTimer
{
public:
	//Thời điểm bắt đầu đếm
	__int64 m_nTimeStart;
	//Thời điểm kết thúc đếm
	__int64 m_nTimeEnd;

	static CTimer* GetInstance();

	/*M+==================================================================
	Method:	    CTimer::~CTimer

	Summary:	Phương thức hủy
	==================================================================-M*/
	~CTimer();

	/*M+==================================================================
	Method:	    CTimer::GetSecondPerTick

	Summary:	Phương thức lấy về khoảng thời gian (tính theo giây)
	giữa 2 tick liên tiếp
	==================================================================-M*/
	void GetSecondPerTick();

	/*M+==================================================================
	Method:	    CTimer::StartCount

	Summary:	Phương thức bắt đầu đếm
	==================================================================-M*/
	void StartCount();

	/*M+==================================================================
	Method:	    CTimer::EndCount

	Summary:	Phương thức kết thúc đếm
	==================================================================-M*/
	void EndCount();

	/*M+==================================================================
	Method:	    CTimer::SetMaxFps

	Summary:	Phương thức gán thời gian frame

	Param:		maxFps - Thời gian frame
	==================================================================-M*/
	void SetMaxFps(float maxFps);

	/*M+==================================================================
	Method:	    CTimer::GetTime

	Summary:	Phương thức trả về khoảng thời gian giữa 2 frame liên tiếp
	==================================================================-M*/
	float GetTime();


private:
	/*M+==================================================================
	Method:	    CTimer::CTimer

	Summary:	Phương thức khởi tạo
	==================================================================-M*/
	CTimer();
	//Số tick trên một giây
	__int64 m_nCountPerSec;
	//Tỉ lệ giữa tick và giây (số giây giữa 2 tick liên tiếp)
	float m_fTimeScale;
	//Số Frame trên một giây tối đa
	float m_fLockFps;
	//Thời gian delta time tính theo giây giữa 2 frame liên tiếp
	float m_fDeltaTime;
	//Thời gian delta time trong một giây
	int m_nFrameRate;

	static CTimer* s_TimerInstance;
};
