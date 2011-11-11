/*
 *  eyeMesh.cpp
 *  membajakTV
 *
 *  Created by Budi Prakosa on 11/9/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "eyeMesh.h"

eyeMesh::eyeMesh()
{
	meshScale = 1;
	
	meshSizeX = 100;
	meshSizeY = 100;
	
	meshGridX = 6;
	meshGridY = 5;
	
	meshTexW = 640;
	meshTexH = 480;
	
	updateMeshTexCoord();
	
}

void eyeMesh::updateMeshTexCoord()
{
	for (int i = 0; i<meshGridX; i++) {
		for (int j = 0; j<meshGridY; j++) {
			meshTexCoord[i][j][0] = ((float)i/(float)(meshGridX-1))*(float)meshTexW;
		    meshTexCoord[i][j][1] = ((float)j/(float)(meshGridY-1))*(float)meshTexH;		
			
		}
	}
}

void eyeMesh::updateMeshVerCoord()
{
	
	
	meshMaxW = (float) meshScale * (((float)meshGridX-1.0f)*(float)meshSizeX - 1.0f);
	meshMaxH = (float) meshScale * ((float)meshGridY*(float)meshSizeY -1);
	
	//glTranslatef(-maxW/2, -maxH/2, 0);
	
	for (int i=0; i<(meshGridX-1) ; i++)
    {
		for (int j = 0; j < meshGridY ; j++)
		{
			meshVerCoord[i][j][0]	= (float)meshScale * ((float)i*(float)meshSizeX - 1);
			meshVerCoord[i][j][1]   = (float)meshScale * ((float)j*(float)meshSizeY -1);
			meshVerCoord[i+1][j][0] = (float)meshScale * (((float)i+1)*(float)meshSizeX - 1);
			meshVerCoord[i+1][j][1] = (float)meshScale * ((float)j*(float)meshSizeY -1);
		}
    }	
}

void eyeMesh::draw(GLenum drawMode)
{
	glPushMatrix();
	
	glTranslatef(-meshMaxW/2, -meshMaxH/2, 0);

	for (int i=0; i<(meshGridX-1) ; i++)
    {
		glBegin(drawMode);
		for (int j = 0; j < meshGridY ; j++)
		{
			glTexCoord2f(meshTexCoord[i][j][0], meshTexCoord[i][j][1]); glVertex3f(meshVerCoord[i][j][0], meshVerCoord[i][j][1], 0.0f);
			glTexCoord2f(meshTexCoord[i+1][j][1], meshTexCoord[i+1][j][1]); glVertex3f(meshVerCoord[i+1][j][0], meshVerCoord[i+1][j][1], 0.0f);			
		}
		glEnd();
	}
	
	glPopMatrix();
}


void eyeMesh::setMeshGrid(int gridW, int gridH)
{
	meshGridX = gridW; 
	meshGridY =	gridH;
}

void eyeMesh::setMeshSize(float sizeX, float sizeY)
{
	meshSizeX = sizeX;
	meshSizeY = sizeY;
}

void eyeMesh::setMeshScale(int scale)
{
	meshScale = scale;
}


void eyeMesh::setMeshTextureSize(int width, int height)
{
	meshTexW = width;
	meshTexH = height;
}

