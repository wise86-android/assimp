/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2014, assimp team

All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
copyright notice, this list of conditions and the
following disclaimer.

* Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other
materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
contributors may be used to endorse or promote products
derived from this software without specific prior
written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/
#include "UnitTestPCH.h"

#include "../../include/assimp/postprocess.h"
#include "../../include/assimp/scene.h"
#include <assimp/Importer.hpp>
#include <BaseImporter.h>


using namespace std;
using namespace Assimp;

class Issue781 : public ::testing::Test
{
public:

    virtual void SetUp() { pImp = new Importer(); }
    virtual void TearDown() { delete pImp; }

protected:
    Importer* pImp;
};



TEST_F(Issue781, colladaLeak){
	FILE* f = NULL;
	f = fopen( ASSIMP_TEST_MODELS_DIR "/Collada/cube.dae", "rb" );

	long p = ftell(f);
	fseek(f, 0, SEEK_END);
	int size = (int)ftell(f);
	fseek(f, p, SEEK_SET);

	unsigned char* buffer = new unsigned char[size];
	fread( buffer, 1, size, f );
	fclose(f);
	unsigned int flags = 0
		| aiProcess_Triangulate
		| aiProcess_CalcTangentSpace
		| aiProcess_SortByPType
		;

	Assimp::Importer* assimpImporter = new Assimp::Importer();
	const aiScene* aiscene = assimpImporter->ReadFileFromMemory(buffer, size, flags, "dae" );


	delete [] buffer;
	delete assimpImporter;

}

