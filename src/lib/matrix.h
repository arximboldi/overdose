//*************************************************************************
// 030324
// Matrix template
//
//*************************************************************************

#ifndef _MATRIX
#define _MATRIX

#include <stdio.h>

const float MINIMUM_VALUE_INVERT_MATRIX=1.0e-20;

template <class Type> class _vertex2;
template <class Type> class _vertex3;
template <class Type> class _vertex4;

template <class Type> class _matrix4;

typedef _matrix4<float> 	_matrix4f;
typedef _matrix4<double> 	_matrix4d;

//*************************************************************************
//
//*************************************************************************

template <class Type>
class _matrix4
{
 public:

  _matrix4(	Type A00=1,Type A01=0,Type A02=0,Type A03=0,
		Type A10=0,Type A11=1,Type A12=0,Type A13=0,
		Type A20=0,Type A21=0,Type A22=1,Type A23=0,
		Type A30=0,Type A31=0,Type A32=0,Type A33=1);
  _matrix4(_matrix4<Type> &mat);

  _matrix4 &operator()(Type A00=1,Type A01=0,Type A02=0,Type A03=0,
		       Type A10=0,Type A11=1,Type A12=0,Type A13=0,
		       Type A20=0,Type A21=0,Type A22=1,Type A23=0,
		       Type A30=0,Type A31=0,Type A32=0,Type A33=1);
  _matrix4 &operator()(_matrix4<Type> &mat);

  _matrix4 	&identity();
  _matrix4 	&null();
  int   		dimension(){return 4;};
  inline 		void assign(int Row,int Col,Type Value1){Value[Row][Col]=Value1;};
  inline 		void set(int Row,int Col,Type Value1){Value[Row][Col]=Value1;};
  inline		Type get(int Row,int Col){return Value[Row][Col];};

  _matrix4	&operator=(_matrix4 &Mat);
  _matrix4 	&operator+(_matrix4 &Mat);
  _matrix4 	&operator+=(_matrix4 &Mat);
  _matrix4 	&operator-(_matrix4 &Mat);
  _matrix4 	&operator-=(_matrix4 &Mat);
  _matrix4 	&operator*(Type Value);
  _matrix4 	&operator*=(Type Value);
  _matrix4 	&operator*(_matrix4 &Mat);
  _matrix4 	&operator*=(_matrix4 &Mat);
  _matrix4 	&operator/(Type Value);
  _matrix4 	&operator/=(Type Value);
  _matrix4 	&transpose();
  _matrix4 	&invert(bool &Result);

  _matrix4 	&translate(Type Dx=0,Type Dy=0,Type Dz=0);
  _matrix4 	&translate(_vertex3<Type> &Vertex1);
  _matrix4 	&scale(Type Sx=1,Type Sy=1,Type Sz=1);
  _matrix4 	&scale(_vertex3<Type> &Vertex1);
  _matrix4 	&rotate_axis_x(Type Angle=0);
  _matrix4 	&rotate_axis_y(Type Angle=0);
  _matrix4 	&rotate_axis_z(Type Angle=0);

  //_matrix4 clone(){_matrix4<Type> Mat1(*this);return Mat1;};
  //Type 		*matriz(){return (Type *) Matriz;};

  _matrix4 	clone(){_matrix4<Type> Mat1(*this);return Mat1;};
  void     	show_values();


 private:
  Type Value[4][4];

  Type 			row_max(int Row,int &Position);
  _matrix4 	&swap_rows(int Row1,int Row2);
  _matrix4 	&swap_columns(int Col1,int Col2);

};

typedef _matrix4<float> _matrix4f;
typedef _matrix4<double> _matrix4d;

//*************************************************************************
//
//*************************************************************************


template <class Type>
_matrix4<Type>::_matrix4(Type A00,Type A01,Type A02,Type A03,
			 Type A10,Type A11,Type A12,Type A13,
			 Type A20,Type A21,Type A22,Type A23,
			 Type A30,Type A31,Type A32,Type A33)
{
  Value[0][0]=A00;Value[0][1]=A01;Value[0][2]=A02;Value[0][3]=A03;
  Value[1][0]=A10;Value[1][1]=A11;Value[1][2]=A12;Value[1][3]=A13;
  Value[2][0]=A20;Value[2][1]=A21;Value[2][2]=A22;Value[2][3]=A23;
  Value[3][0]=A30;Value[3][1]=A31;Value[3][2]=A32;Value[3][3]=A33;
}


//*************************************************************************
//
//*************************************************************************

template <class Type>
_matrix4<Type>::_matrix4(_matrix4<Type> &mat)
{

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]=mat.get(i,j);
	}
    }
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator()(Type a00,Type a01,Type a02,Type a03,
			   Type a10,Type a11,Type a12,Type a13,
			   Type a20,Type a21,Type a22,Type a23,
			   Type a30,Type a31,Type a32,Type a33)
{
  Value[0][0]=a00;Value[0][1]=a01;Value[0][2]=a02;Value[0][3]=a03;
  Value[1][0]=a10;Value[1][1]=a11;Value[1][2]=a12;Value[1][3]=a13;
  Value[2][0]=a20;Value[2][1]=a21;Value[2][2]=a22;Value[2][3]=a23;
  Value[3][0]=a30;Value[3][1]=a31;Value[3][2]=a32;Value[3][3]=a33;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator()(_matrix4<Type> &mat)
{

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]=mat.get(i,j);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::identity()
{
  Value[0][0]=1;Value[0][1]=0;Value[0][2]=0;Value[0][3]=0;
  Value[1][0]=0;Value[1][1]=1;Value[1][2]=0;Value[1][3]=0;
  Value[2][0]=0;Value[2][1]=0;Value[2][2]=1;Value[2][3]=0;
  Value[3][0]=0;Value[3][1]=0;Value[3][2]=0;Value[3][3]=1;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::null()
{
  Value[0][0]=0;Value[0][1]=0;Value[0][2]=0;Value[0][3]=0;
  Value[1][0]=0;Value[1][1]=0;Value[1][2]=0;Value[1][3]=0;
  Value[2][0]=0;Value[2][1]=0;Value[2][2]=0;Value[2][3]=0;
  Value[3][0]=0;Value[3][1]=0;Value[3][2]=0;Value[3][3]=0;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator=(_matrix4<Type> &mat)
{

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]=mat.get(i,j);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

  template <class Type> _matrix4<Type> &
  _matrix4<Type>::operator+(_matrix4<Type> &mat)
  {
    _matrix4<Type> mat1(*this);

    for (int i=0;i<4;i++)
      {
	for (int j=0;j<4;j++)
	  {
	    mat1.assign(i,j,Value[i][j]+mat.get(i,j));
	  }
      }
    return(mat1);
  }

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator+=(_matrix4<Type> &mat)
{

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]+=mat.get(i,j);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator-(_matrix4<Type> &mat)
{
  _matrix4<Type> mat1(*this);

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  mat1.assign(i,j,Value[i][j]-mat.get(i,j));
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator-=(_matrix4<Type> &mat)
{

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]-=mat.get(i,j);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator*(Type Value1)
{
  _matrix4<Type> mat1(*this);

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  mat1.assign(i,j,Value[i][j]*Value1);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator*=(Type Value1)
{
  _matrix4<Type> mat1(*this);

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]*=Value1;
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator*(_matrix4<Type> &mat)
{
  _matrix4<Type> mat1(*this),mat2;
  Type sum;

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  sum=0;
	  for (int k=0;k<4;k++)
	    {
	      sum+=mat1.get(i,k)*mat.get(k,j);
	    }
	  mat2.assign(i,j,sum);
	}
    }
  return(mat2);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator*=(_matrix4<Type> &mat)
{
  _matrix4<Type> mat1(*this),mat2;
  Type sum;

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  sum=0;
	  for (int k=0;k<4;k++)
	    {
	      sum+=mat1.get(i,k)*mat.get(k,j);
	    }
	  Value[i][j]=sum;
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator/(Type Value1)
{
  _matrix4<Type> mat1(*this);

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  mat1.assign(i,j,Value[i][j]/Value1);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::operator/=(Type Value1)
{
  _matrix4<Type> mat1(*this);

  for (int i=0;i<4;i++)
    {
      for (int j=0;j<4;j++)
	{
	  Value[i][j]/=Value1;
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::translate(Type Dx,Type Dy,Type Dz)
{

  this->identity();
  Value[3][0]=Dx;
  Value[3][1]=Dy;
  Value[3][2]=Dz;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::translate(_vertex3<Type> &Vertex1)
{

  this->identity();
  Value[3][0]=Vertex1.x;
  Value[3][1]=Vertex1.y;
  Value[3][2]=Vertex1.z;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::scale(Type Sx,Type Sy,Type Sz)
{

  this->identity();
  Value[0][0]=Sx;
  Value[1][1]=Sy;
  Value[2][2]=Sz;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::scale(_vertex3<Type> &Vertex1)
{

  this->identity();
  Value[0][0]=Vertex1.x;
  Value[1][1]=Vertex1.y;
  Value[2][2]=Vertex1.z;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::rotate_axis_x(Type Angle1)
{
  Type Angle=(Angle1*M_PI)/180.;
  Type cosinus=cos(Angle),sinus=sin(Angle);

  this->identity();
  Value[1][1]=cosinus;
  Value[1][2]=sinus;
  Value[2][1]=-sinus;
  Value[2][2]=cosinus;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::rotate_axis_y(Type Angle1)
{
  Type Angle=(Angle1*M_PI)/180.;
  Type cosinus=cos(Angle),sinus=sin(Angle);

  this->identity();
  Value[0][0]=cosinus;
  Value[0][2]=-sinus;
  Value[2][0]=sinus;
  Value[2][2]=cosinus;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::rotate_axis_z(Type Angle1)
{
  Type Angle=(Angle1*M_PI)/180.;
  Type cosinus=cos(Angle),sinus=sin(Angle);

  this->identity();
  Value[0][0]=cosinus;
  Value[1][0]=-sinus;
  Value[0][1]=sinus;
  Value[1][1]=cosinus;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::transpose()
{
  _matrix4<Type> mat(*this);
  int i,j;

  for (i=0;i<4;i++)
    {
      for (j=0;j<4;j++)
	{
	  Value[i][j]=mat.get(j,i);
	}
    }
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::invert(bool &Result)
{
  _matrix4<Type> Identity;
  Type Max,Factor;
  int i,j,k,Position;

  for (i=0;i<4;i++)
    {
      Max=row_max(i,Position);
      if (fabs(Max)<MINIMUM_VALUE_INVERT_MATRIX)
	{
	  Result=false;
	  return(*this);
	}
      Factor=1/Max;
      if (i!=Position)
	{
	  swap_rows(i,Position);
	  Identity.swap_rows(i,Position);
	}
      if (Factor!=1)
	{
	  for (j=i;j<4;j++) Value[i][j]*=Factor;
	  for (j=0;j<4;j++) Identity.assign(i,j,Identity.get(i,j)*Factor);    
	}
      for (j=0;j<4;j++)
	{
	  if (j!=i)
	    {
	      Factor=-Value[j][i];
	      if (Factor!=0)
		{
		  for (k=i;k<4;k++) Value[j][k]+=Factor*Value[i][k];
		  for (k=0;k<4;k++) 
		    Identity.assign(j,k,Identity.get(j,k)+Factor*Identity.get(i,k));
		}
	    }
	}
    }
  Result=true;	
  *this=Identity;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> Type 
_matrix4<Type>::row_max(int Row,int &Position)
{
  Type Max=0;

  Position=Row;
  for (int i=Row;i<4;i++)
    {
      if ((fabs(Value[i][Row]))>fabs(Max))
	{
	  Max=Value[i][Row];
	  Position=i;
	}
    }
  return Max;
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::swap_rows(int Row1,int Row2)
{
  Type a0,a1,a2,a3;

  a0=Value[Row1][0];
  a1=Value[Row1][1];
  a2=Value[Row1][2];
  a3=Value[Row1][3];
  Value[Row1][0]=Value[Row2][0];
  Value[Row1][1]=Value[Row2][1];
  Value[Row1][2]=Value[Row2][2];
  Value[Row1][3]=Value[Row2][3];
  Value[Row2][0]=a0;
  Value[Row2][1]=a1;
  Value[Row2][2]=a2;
  Value[Row2][3]=a3;
  return(*this);
}

//*************************************************************************
//
//*************************************************************************

template <class Type> _matrix4<Type> &
_matrix4<Type>::swap_columns(int col1,int col2)
{
  Type a0,a1,a2,a3;

  a0=Value[0][col1];
  a1=Value[1][col1];
  a2=Value[2][col1];
  a3=Value[3][col1];
  Value[0][col1]=Value[0][col2];
  Value[1][col1]=Value[1][col2];
  Value[2][col1]=Value[2][col2];
  Value[3][col1]=Value[3][col2];
  Value[0][col2]=a0;
  Value[1][col2]=a1;
  Value[2][col2]=a2;
  Value[3][col2]=a3;
  return(*this);
}


//*************************************************************************
//
//*************************************************************************

template <class Type> void 
_matrix4<Type>::show_values()
{

  printf("%10d%10d%10d%10d\n",0,1,2,4);
  for (int i=0;i<4;i++)
    {
      printf("%d  ",i);
      for (int j=0;j<4;j++)
	{
	  printf(" %8.3f ",Value[i][j]);
	}
      puts("");
    }
}


/*
*************************************************************************
//
*************************************************************************

int main()
{
_matrix4 mat1(2,1,0,0,0,3,1,0,0,4,0,1,0,1,0,1),mat2;
_matrix4 mat3(mat1);
punto3r vec31(1,2,3),vec32(5,6,7);

mat1.invertir();
mat3*=mat1;
mat3.mostrar("producto");
mat1.trasladar(punto3r(1,2,3));
mat1.trasladar(vec31);
mat2=mat1+mat1;
vec31=3*vec31;
vec41=vec31;
vec41=vec31*mat1*mat2;
vec41=vec41*mat1;
vec31=vec41;
mat1.mostrar("mat1");
vec31.mostrar("vec31");
vec41.mostrar("vec41");

vec31.normalizado().mostrar(" vec4 normalizado");
vec41.mostrar("vec4 otra vez");
printf("escalar %8.3lf 
",vec31^vec32);
vec31=vec31&vec32;
vec31.mostrar("vec3 vectorial");
mat1.mostrar("mat1");
mat2.mostrar("mat2");

return 0;
}

*/
#endif
