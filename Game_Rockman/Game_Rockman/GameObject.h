#pragma once
/*+========================================================
File:		GameObject.h
Sumary:	Định nghĩa lớp GameObject tổng quát
========================================================+*/
#include "ResourcesManager.h"

class CGameObject
{
private:
public:
	CGameObject();

	/*M+==================================================================
	Method:	    CGameObject::CGameObject

	Summary:	Phương thức khởi tạo có tham số

	Params:		pos - Vị trí của Object
	id - ID của object
	typeID - ID của loại object
	==================================================================-M*/
	CGameObject(D3DXVECTOR2 pos, int id, int typeID, int val1 = 0, int val2 = 0);
};