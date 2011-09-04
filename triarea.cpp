int triarea(int xx1,int yy1,int xx2,int yy2,int xx3,int yy3)
{
	// returns twice the area ;
	int Vx1,Vx2,Vy1,Vy2,area;
	
	Vx1=xx3-xx1;
	Vy1=yy3-yy1;
	Vx2=xx2-xx1;
	Vy2=yy2-yy1;
	
	area=Vx1*Vy2-Vy1*Vx2;
	return abs(area);
}
