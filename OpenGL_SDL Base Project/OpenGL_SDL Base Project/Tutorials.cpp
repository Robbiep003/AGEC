//--------------------------------------------------------------------------------------------------

//Tutorial - Primitives - Polygons
//void Draw2DSquare()
//{
//	glBegin(GL_POLYGON);
//	glVertex3f(-0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(-0.5f, -1.0f, 0.0f);
//	glEnd();
//}

//--------------------------------------------------------------------------------------------------

//void DrawPoints()
//{
//	glBegin(GL_POINTS);
//	glVertex3f(-0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(-0.5f, -1.0f, 0.0f);
//	glEnd();
//}
//
//void DrawTriangles()
//{
//	glBegin(GL_TRIANGLES);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glEnd();
//}
//
//void DrawQuads()
//{
//	glBegin(GL_QUADS);
//	glVertex3f(-0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(-0.5f, -1.0f, 0.0f);
//	glEnd();
//}
//
//void DrawTriangleStrip()
//{
//	glBegin(GL_TRIANGLE_STRIP);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glEnd();
//}
//
//void DrawTriangleFan()
//{
//	glBegin(GL_TRIANGLE_FAN);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(0.0f, 0.0f, 0.0f);
//	glEnd();
//}
//
//void DrawQuadStrip()
//{
//	glBegin(GL_QUAD_STRIP);
//	glVertex3f(-0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, 0.0f, 0.0f);
//	glVertex3f(0.5f, -1.0f, 0.0f);
//	glVertex3f(-0.5f, -1.0f, 0.0f);
//	glEnd();
//}

//--------------------------------------------------------------------------------------------------

//glbegin(gl_triangles);
//	glcolor3f(1.0f, 0.0f, 0.0f);
//	glvertex3f(2.0f, 2.5f, -1.0f);
//	glcolor3f(0.0f, 1.0f, 0.0f);
//	glvertex3f(-3.5f, -2.5f, -1.0f);
//	glcolor3f(0.0f, 0.0f, 1.0f);
//	glvertex3f(2.0f, -4.0f, 0.0f);
//glend();

//--------------------------------------------------------
//Tutorial - Primitaves - POINTS
//float pointSize = 0.5f;

////Draw a line of points of increasing size.
//for (float point = -4.0f; point < 5.0f; point += 0.5f)
//{
//	//Set the point size.
//	glPointSize(pointSize);

//	//Draw the point.
//	glBegin(GL_POINTS);
//	glVertex3f(point, 0.0f, 0.0f);
//	glEnd();

//	//Increase the size of the point.
//	pointSize += 0.5f;
//}
//--------------------------------------------------------

//--------------------------------------------------------
//Tutorial - Primitives - LINES
//float lineWidth = 0.5f;

////Draw a series of lines of increasing width.
//for (float line = 0.0f; line < 7.0f; line += 0.5f)
//{
//	//Set the line width.
//	glLineWidth(lineWidth);

//	glBegin(GL_LINES);
//		glVertex3f(-0.5f, line - 3.0f, 0.0f);
//		glVertex3f(-4.5f, line - 3.0f, 0.0f);
//	glEnd();

//	//Increase the line width for the next line.
//	lineWidth += 1.0f;
//}

////Reset the line width.
//lineWidth = 0.5f;

////Enable stippling.
//glEnable(GL_LINE_STIPPLE);

//// 0XAAAA = 1010 1010 1010 1010
//short stipplePattern = 0xAAAA;

////Set the stipple pattern.
//glLineStipple(2, stipplePattern);

////Draw a series of lines of increasing width.
//for (float line = 0.0f; line < 7.0f; line += 0.5f)
//{
//	//Set the line width.
//	glLineWidth(lineWidth);

//	glBegin(GL_LINES);
//		glVertex3f(0.5f, line - 3.0f, 0.0f);
//		glVertex3f(4.5f, line - 3.0f, 0.0f);
//	glEnd();

//	//Increase the line width for the next line.
//	lineWidth += 1.0f;
//}

//glDisable(GL_LINE_STIPPLE);
//--------------------------------------------------------

//--------------------------------------------------------
//Tutorial - Primitives - Polygons
//static float angle = 0.0f;

////Default setting.
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

////Draw FRONT faces as lines.
//glPolygonMode(GL_FRONT, GL_LINE);
//glPushMatrix();
//	glTranslatef(-4.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glColor3f(1.0f, 0.0f, 0.0f);
//	Draw2DSquare();
//glPopMatrix();

////Reset to default.
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

////Draw BACK face as points.
//glPolygonMode(GL_BACK, GL_POINT);
//glPushMatrix();
//	glTranslatef(-2.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);
//	Draw2DSquare();
//glPopMatrix();

////Reset to default.
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

////Draw both faces.
//glPushMatrix();
//	glTranslatef(0.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);
//glPopMatrix();

////Draw BACK face as lines.
//glPolygonMode(GL_BACK, GL_LINE);
//glPushMatrix();
//	glTranslatef(2.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glColor3f(1.0f, 0.0f, 1.0f);
//	Draw2DSquare();
//glPopMatrix();

////Draw FRONT and BACK as lines.
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//glPushMatrix();
//	glTranslatef(4.0f, 0.0f, 0.0f);
//	glRotatef(angle, 0.0f, 1.0f, 0.0f);
//	glColor3f(1.0f, 1.0f, 0.0f);
//	Draw2DSquare();
//glPopMatrix();

////Reset to default.
//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//
////Alter the angle to ensure rotation.
//angle += 0.2f;
//--------------------------------------------------------

//--------------------------------------------------------
//Tutorial - Primitives - Triangles

//Top left
//glPushMatrix();
//glTranslatef(-6.5f, 1.5f, 0.0f);
//DrawPoints();
//glPopMatrix();

//Top middle
//glPushMatrix();
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glTranslatef(-1.5f, 1.5f, 0.0f);
//DrawTriangles();
//glPopMatrix();

//Top right
//glPushMatrix();
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glTranslatef(3.5f, 1.5f, 0.0f);
//DrawQuads();
//glPopMatrix();

//Bottom left
//glPushMatrix();
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glTranslatef(-6.5f, -2.5f, 0.0f);
//DrawTriangleStrip();
//glPopMatrix();

//Bottom middle
//glPushMatrix();
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glTranslatef(-1.5f, -2.5f, 0.0f);
//DrawTriangleFan();
//glPopMatrix();

//Bottom right
//glPushMatrix();
//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//glTranslatef(3.5f, -2.5f, 0.0f);
//DrawQuadStrip();
//glPopMatrix();
//--------------------------------------------------------

//SetLight(1);
//SetMaterial(1);
////glutSolidSphere(3.0, 20, 20);
//
//glPushMatrix();
//glRotatef(rotation, 1, 1, 1);
//pyramid->Draw();
//glPopMatrix();

//glPushMatrix();
//glRotatef(rotation, 1, 1, 1);
//pyramid->Draw();
//glPopMatrix();