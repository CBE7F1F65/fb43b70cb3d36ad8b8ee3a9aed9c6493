#include "../Header/BIOInterface.h"

float BIOInterface::Math_Transform3DPoint(float &x, float &y, float &z, bio3DPoint *ptfar)
{
	if (!ptfar || ptfar->z == 0.0f)
	{
		return 1.0f;
	}
	float scale = (ptfar->z - z) / ptfar->z;
	x = (x - ptfar->x) * scale + ptfar->x;
	y = (y - ptfar->y) * scale + ptfar->y;
	z = 0;
	return scale;
}
// end

BIOMATRIX * BIOInterface::Math_MatrixIdentity(BIOMATRIX * pOut)
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixIdentity(pOut);
#else

	ZeroMemory(pOut, sizeof(BIOMATRIX));
	pOut->_11 = 1.0f;
	pOut->_22 = 1.0f;
	pOut->_33 = 1.0f;
	pOut->_44 = 1.0f;

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixTranslation( BIOMATRIX *pOut, float x, float y, float z )
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixTranslation(pOut, x, y, z);
#else

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._41 = x;
	mul._42 = y;
	mul._43 = z;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixRotationX( BIOMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixRotationX(pOut, angle);
#else

	float sinval=sinf(angle);
	float cosval=cosf(angle);

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._22 = cosval;
	mul._23 = sinval;
	mul._32 = -sinval;
	mul._33 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixRotationY( BIOMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixRotationY(pOut, angle);
#else

	float sinval=sinf(angle);
	float cosval=cosf(angle);

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = cosval;
	mul._13 = -sinval;
	mul._31 = sinval;
	mul._33 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixRotationZ( BIOMATRIX *pOut, float angle )
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixRotationZ(pOut, angle);
#else

	float sinval=sinf(angle);
	float cosval=cosf(angle);

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = cosval;
	mul._12 = sinval;
	mul._21 = -sinval;
	mul._22 = cosval;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixScaling( BIOMATRIX *pOut, float sx, float sy, float sz )
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixScaling(pOut, sx, sy, sz);
#else

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	mul._11 = sx;
	mul._22 = sy;
	mul._33 = sz;
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

BIOMATRIX * BIOInterface::Math_MatrixMultiply( BIOMATRIX *pOut, const BIOMATRIX *pM1, const BIOMATRIX *pM2 )
{
	if (!pOut || !pM1 || ! pM2)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixMultiply(pOut, pM1, pM2);
#else

	BIOMATRIX outmat;
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			outmat.m[i][j] = 0.0f;
			for (int k=0; k<4; k++)
			{
				outmat.m[i][j] += pM1->m[i][k] * pM2->m[k][j];
			}
		}
	}
	for (int i=0; i<4; i++)
	{
		for (int j=0; j<4; j++)
		{
			pOut->m[i][j] = outmat.m[i][j];
		}
	}

#endif // __WIN32
	return pOut;
}

BIOMATRIX*	BIOInterface::Math_MatrixOrthoOffCenterLH(BIOMATRIX *pOut, float l, float r, float b, float t, float zn, float zf)
{
	if (!pOut)
	{
		return NULL;
	}
#if defined __WIN32 && defined USE_D3D
	D3DXMatrixOrthoOffCenterLH(pOut, l, r, b, t, zn, zf);
#else

	BIOMATRIX mul;
	Math_MatrixIdentity(&mul);
	if (r != l && t != b && zf != zn)
	{
		mul._11 = 2/(r-l);
		mul._22 = 2/(t-b);
		mul._33 = 1/(zf-zn);
		mul._41 = (l+r)/(l-r);
		mul._42 = (t+b)/(b-t);
		mul._43 = zn/(zn-zf);
	}
	Math_MatrixMultiply(pOut, pOut, &mul);

#endif // __WIN32
	return pOut;
}

char * BIOInterface::Math_itoa(int ival, char * buffer)
{
	if (!buffer)
	{
		return NULL;
	}
	sprintf(buffer, "%d", ival);
	return buffer;
}

int BIOInterface::Math_atoi(const char * buffer)
{
	return atoi(buffer);
}

char * BIOInterface::Math_ftoa(float fval, char * buffer)
{
	if (!buffer)
	{
		return NULL;
	}
	sprintf(buffer, "%f", fval);
	return buffer;
}

float BIOInterface::Math_atof(const char * buffer)
{
	return atof(buffer);
}

LONGLONG BIOInterface::Math_atoll(const char *buffer)
{
#ifdef __WIN32
	return _atoi64(buffer);
#else

	LONGLONG llret = 0;
	int mul = 10;
	if (strlen(buffer) >= 2)
	{
		if (buffer[0] == '0' && buffer[1] != 'x' && buffer[1] != 'X')
		{
			mul = 8;
		}
		else if (buffer[0] == 'x' || buffer[1] == 'x' || buffer[0] == 'X' || buffer[1] == 'X')
		{
			mul = 16;
		}
	}
	int nowbit = 0;
	for (int i=strlen(buffer)-1; i>=0; i--, nowbit++)
	{
		LONGLONG val = buffer[i] - '0';
		if (mul == 16)
		{
			if (buffer[i] > 'a' && buffer[i] <= 'f')
			{
				val += '9' - 'a' + 1;
			}
			if (buffer[i] > 'A' && buffer[i] <= 'F')
			{
				val += '9' - 'A' + 1;
			}
		}
		if (val < 0 || val > mul)
		{
			break;
		}
		for (int j=0; j<nowbit; j++)
		{
			val = val * mul;
		}
		llret += val;
	}
	return llret;

#endif // __WIN32
}


DWORD BIOInterface::Math_HSVAtoARGB(float h, float s, float v, float a)
{
	float r, g, b;
	float xh, i, p1, p2, p3;

	if (s == 0)
	{
		r = v;
		g = v;
		b = v;
	}
	else
	{
		xh = h * 6;
		if(xh == 6) xh=0;
		i = floorf(xh);
		p1 = v * (1 - s);
		p2 = v * (1 - s * (xh - i));
		p3 = v * (1 - s * (1 - (xh - i)));

		if      (i == 0) {r = v;  g = p3; b = p1;}
		else if (i == 1) {r = p2; g = v;  b = p1;}
		else if (i == 2) {r = p1; g = v;  b = p3;}
		else if (i == 3) {r = p1; g = p2; b = v; }
		else if (i == 4) {r = p3; g = p1; b = v; }
		else			 {r = v;  g = p1; b = p2;}
	}

	return (DWORD(a*255.0f)<<24) + (DWORD(r*255.0f)<<16) + (DWORD(g*255.0f)<<8) + DWORD(b*255.0f);
}

void BIOInterface::Math_ARGBtoHSVA(DWORD col, float *_h, float *_s, float *_v, float *_a)
{
	float r, g, b;
	float minv, maxv, delta;
	float del_R, del_G, del_B;
	float h, s, v, a;

	a = (col>>24) / 255.0f;
	r = ((col>>16) & 0xFF) / 255.0f;
	g = ((col>>8)  & 0xFF) / 255.0f;
	b = (col       & 0xFF) / 255.0f;

	minv = M_MIN(M_MIN(r, g), b);
	maxv = M_MAX(M_MAX(r, g), b);
	delta = maxv - minv;

	v = maxv;

	if (delta == 0)
	{
		h = 0;
		s = 0;
	}
	else
	{
		s = delta / maxv;
		del_R = (((maxv - r) / 6) + (delta / 2)) / delta;
		del_G = (((maxv - g) / 6) + (delta / 2)) / delta;
		del_B = (((maxv - b) / 6) + (delta / 2)) / delta;

		if      (r == maxv) {h = del_B - del_G;}
		else if (g == maxv) {h = (1.0f / 3.0f) + del_R - del_B;}
		else if (b == maxv) {h = (2.0f / 3.0f) + del_G - del_R;}

		if (h < 0) h += 1;
		if (h > 1) h -= 1;
	}

	if (_h)
	{
		*_h = h;
	}
	if (_s)
	{
		*_s = s;
	}
	if (_v)
	{
		*_v = v;
	}
	if (_a)
	{
		*_a = a;
	}
}