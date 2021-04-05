global VERTEX_TYPE_GEOMETRY = 0x0001
global VERTEX_TYPE_NORMAL = 0x0002
global VERTEX_TYPE_TANGENT = 0x0004
global VERTEX_TYPE_BINORMAL = 0x0008
global VERTEX_TYPE_TEXTURE1 = 0x0010
global VERTEX_TYPE_TEXTURE2 = 0x0020
global VERTEX_TYPE_DIFFUSE = 0x0040

global HEADER = 0xFF77
global FOOTER = 0x77FF

function ExportMesh Object3D filename CopyTextures RelativeTexturesPath ExportPath =
(
	local vertices = #()
	local indices = #()
	--filename = "E:/vjuab2010/Run/Test/Data/mi1ermesh.mesh"
	--f = getSaveFileName caption:"Save Mesh:" filename:
	/*filename = getSaveFileName \ 
	caption:"Export mesh" \
	filename:(getDir #renderPresets + @"\") \ 
	types:"Object Preset(*.mesh)|*.mesh" \
	historyCategory:"RTTObjectPresets"*/
	
	-- Para crear un fichero en modo escritura binaria
	--DisplayMessage "Costa Rica: Aqui se cura todo!!!"
	
	file=fopen filename "wb"
	-- ENCABEZADO HEXA
	WriteShort file HEADER #unsigned
	------------
	-- Si es un material Standard
	countMaterials = 1
	clase = classof(Object3D.material)
	if clase == Standardmaterial then
	(
		-- numero de materiales
		WriteShort file countMaterials #unsigned
		ExportMaterial Object3D.material file CopyTextures RelativeTexturesPath ExportPath
	)
	else --Si es Multimaterial
	(
		-- numero de materiales
		countMaterials=Object3D.material.count
		WriteShort file countMaterials #unsigned
		for i = 1 to countMaterials do
		(
			ExportMaterial Object3D.material[i] file CopyTextures RelativeTexturesPath ExportPath
		)
	)
	--Creacion del vector del "mesh"
	CreateMesh Object3D vertices indices
	---------------------------------------PRINT IN FILE-----------------------------------------------
	for k=1 to vertices.count do
	(
		cantVertices = vertices[k].count
		--WriteShort file cantVertices #unsigned
		cantIndices = indices[k].count
		--format "Cantidad de Valores: %\n" cantValores
		--format "Cantidad de Vertices: %\n" cantVertices
		WriteShort file cantVertices #unsigned
		--format "vtx count %" vertices[1].count
		for i = 1 to vertices[k].count do
		(
			for j = 1 to vertices[k][i].count do
			(
				/*if j == 7 then
				(
					WriteLong file vertices[k][i][j] #unsigned
					--format "(SHORT) %, " vertices[i][j]
				)
				else*/
				(
					WriteFloat file vertices[k][i][j]
					--format "(FLOAT) %, " vertices[i][j]
				)
			)
			--format " %\n" vertices[i]
			--format "vertices count %\n" vertices[i].count
		)
		WriteShort file cantIndices #unsigned
		for i = 1 to cantIndices do
		(
			WriteShort file indices[k][i] #unsigned
		)
		--format "Indices: %\n" indices
	)
	----------------------------------------------------------------------------------------------------------
	WriteShort file FOOTER #unsigned
	--Para hacer un flush de los bytes no escritos en el fichero
	fflush file
	-- Para cerrar el fichero
	fclose file
)

function ExportMaterial material file CopyTextures RelativeTexturesPath ExportPath =
(
	--Vertex Type
	local vertexType = GetVertexType material
	WriteShort file vertexType #unsigned
	--Cantidad de texturas
	local cantTextures = (CountTextures material)
	WriteShort file cantTextures #unsigned
	--Exporta materiales
	local FileName = ""
	if material.diffuseMapEnable then
	(
		FileName = openBitMap material.diffuseMap.bitmap.filename
		format "Filename: %\n" FileName
		ExportTexturesPath file FileName CopyTextures ExportPath RelativeTexturesPath
	)
	if material.selfIllumMapEnable then
	(
		FileName = openBitMap material.selfIllumMap.bitmap.filename
		format "Filename: %\n" FileName
		ExportTexturesPath file FileName CopyTextures ExportPath RelativeTexturesPath
	)
	if material.bumpMapEnable then
	(
		FileName = openBitMap material.bumpMap.bitmap.filename
		format "Filename: %\n" FileName
		ExportTexturesPath file FileName CopyTextures ExportPath RelativeTexturesPath
	)
	if material.reflectionMapEnable then
	(
		FileName = openBitMap material.reflectionMap.bitmap.filename
		format "Filename: %\n" FileName
		ExportTexturesPath file FileName CopyTextures ExportPath RelativeTexturesPath
	)
)

function CreateVertex position normal diffuseColor tuv1 tuv2  vertexType VertOut =
(
	local vertexOut =#()
	if (bit.and vertexType VERTEX_TYPE_TEXTURE1) == VERTEX_TYPE_TEXTURE1 then
	(
		vertexOut = #(position.x, position.y, position.z, normal.x, normal.y, normal.z, tuv1.x, 1.0-tuv1.y)
	)
	else if (bit.and vertexType VERTEX_TYPE_TEXTURE2) == VERTEX_TYPE_TEXTURE2 then
	(
		vertexOut = #(position.x, position.y, position.z, normal.x, normal.y, normal.z, tuv1.x, 1.0-tuv1.y, tuv2.x, 1.0-tuv2.y)
	)
	else if (bit.and vertexType VERTEX_TYPE_DIFFUSE) == VERTEX_TYPE_DIFFUSE then
	(
		vertexOut = #(position.x, position.y, position.z, normal.x, normal.y, normal.z, diffuseColor)
	)
	join VertOut vertexOut
)

function CreateMesh Object3D vertices indices =
(
	local numFaces = getNumFaces Object3D
	local vertType=#()
	local IsStandardMaterial=(classof(Object3D.material) == Standardmaterial)
	if IsStandardMaterial then
	(
		append vertType (GetVertexType Object3D.material)
	)
	else --Si es Multimaterial
	(
		for i = 1 to Object3D.material.count do
		(
			append vertType (GetVertexType Object3D.material[i])
		)
	)
	
	for i=1 to numFaces do
	(
		local ldsxFace = getFace Object3D i
		local vtx1 = (getVert Object3D ldsxFace.x)
		local vtx2 = (getVert Object3D ldsxFace.y)
		local vtx3 = (getVert Object3D ldsxFace.z)
		
		--MULTIPLICAR VERTICES POR LA INVERSA DE LA MATRIS DE TRANSFORMACION
		local invTransform = inverse Object3D.transform --Inversa
		vtx1 = vtx1 * invTransform
		vtx2 = vtx2 * invTransform
		vtx3 = vtx3 * invTransform
		
		--cara
		vtx1 = RHTranslationToLH (vtx1)
		vtx2 = RHTranslationToLH (vtx2)
		vtx3 = RHTranslationToLH (vtx3)
		
		--normal
		local normal1 = RHTranslationToLH (getNormal Object3D ldsxFace.x)
		local normal2 = RHTranslationToLH (getNormal Object3D ldsxFace.y)
		local normal3 = RHTranslationToLH (getNormal Object3D ldsxFace.z)
		
		--color
		--sustituir en la version final
		--local dColor = 0x7FFFFFFF --Maximo valor que lee C++ sin dar error.
		local dColor = 0xFFFFFF01
		
		--Coordenadas de textura
		local text1 = meshop.getMapFace Object3D 1 i
		--TUV1
		local TUV1Map1 = meshop.getMapVert Object3D 1 text1.x
		local TUV1Map2 = meshop.getMapVert Object3D 1 text1.y
		local TUV1Map3 = meshop.getMapVert Object3D 1 text1.z
		--TUV2
		local TUV2Map1 = TUV1Map1
		local TUV2Map2 = TUV1Map2
		local TUV2Map3 = TUV1Map3
		
		local IdMapMaterial=1
		if IsStandardMaterial==false then
		(
			IdMapMaterial=getFaceMatID Object3D i
		)
		
		if (bit.and vertType[IdMapMaterial] VERTEX_TYPE_TEXTURE2)==VERTEX_TYPE_TEXTURE2 then
		(
			--Si tiene el TUV2
			local text2 = meshop.getMapFace Object3D 2 i
			TUV2Map1 = meshop.getMapVert Object3D 2 text2.x
			TUV2Map2 = meshop.getMapVert Object3D 2 text2.y
			TUV2Map3 = meshop.getMapVert Object3D 2 text2.z
		)
		
		local VertOut1 = #()
		local VertOut2 = #()
		local VertOut3 = #()
		
		CreateVertex vtx1 normal1 dColor TUV1Map1 TUV2Map1 vertType[IdMapMaterial] VertOut1
		--format "1 - %: %\n" i VertOut1
		CreateVertex vtx2 normal2 dColor TUV1Map2 TUV2Map2 vertType[IdMapMaterial] VertOut2
		--format "2 - %: %\n" i VertOut2
		CreateVertex vtx3 normal3 dColor TUV1Map3 TUV2Map3 vertType[IdMapMaterial] VertOut3
		--format "3 - %: %\n" i VertOut3
		
		AddVertex IdMapMaterial vertices VertOut1 indices
		AddVertex IdMapMaterial vertices VertOut3 indices
		AddVertex IdMapMaterial vertices VertOut2 indices
	)
)

function RHTranslationToLH translation =
(
	return point3 translation.x translation.z translation.y
)
function GetVertexType material =
(
	local mascara = bit.or VERTEX_TYPE_GEOMETRY VERTEX_TYPE_NORMAL
	if material.diffuseMapEnable AND material.diffuseMap != undefined then
	(
		if material.selfIllumMapEnable AND material.selfIllumMap != undefined then
		(
			mascara = bit.or mascara VERTEX_TYPE_TEXTURE2
		)
		else
		(
			mascara = bit.or mascara VERTEX_TYPE_TEXTURE1
		)
		if material.bumpMapEnable AND material.bumpMap != undefined then
		(
			mascara = bit.or mascara VERTEX_TYPE_TANGENT
			mascara = bit.or mascara VERTEX_TYPE_BINORMAL
		)
	)
	else
	(
		mascara = bit.or mascara VERTEX_TYPE_DIFFUSE
	)
	format "DEBUG: Vertex Type: %\n" mascara
	return mascara
)

function AddVertex IdMapMaterial VertexBuffer vtx1  indices =
(
	while VertexBuffer.count<IdMapMaterial do
	(
		append VertexBuffer (#())
	)
	local exist = FindVertex IdMapMaterial VertexBuffer vtx1
	if exist == -1 then
	(
		exist = VertexBuffer[IdMapMaterial].count
		append VertexBuffer[IdMapMaterial] vtx1
	)
	AddIndex IdMapMaterial indices exist
)

function AddIndex IdMapMaterial indices indice =
(
	while indices.count<IdMapMaterial do
	(
		append indices (#())
	)
	append indices[IdMapMaterial] indice
)

function FindVertex IdMapMaterial Vertices vtx =
(
	local size = Vertices[IdMapMaterial].count
	for i = 1 to size do
	(
		local IdFound=true
		for j=1 to Vertices[IdMapMaterial][i].count do
		(
			if Vertices[IdMapMaterial][i][j]!=vtx[j] then
				IdFound=false
		)
		if IdFound then
		(
			return i-1
		)
	)
	return -1
)
function CountTextures material =
(
	local cant = 0
	if material.diffuseMapEnable then
	(
		cant = cant + 1
	)
	if material.selfIllumMapEnable then
	(
		cant = cant + 1
	)
	if material.bumpMapEnable then
	(
		cant = cant + 1
	)
	if material.reflectionMapEnable then
	(
		cant = cant + 1
	)
	format "DEBUG: Cantidad de Texturas: %\n" cant
	return cant
)
function DisplayMessage message =
(
	messageBox message --title:"Exporting Mesh" beep:true
)
function DisplayWarning message =
(
	messageBox message title:"Warning Message" beep:true
)
function DisplayError message =
(
	messageBox message title:"Error Message" beep:true
)

function ExportTexturesPath file FileName CopyTextures ExportPath RelativeTexturesPath =
(
	local AbsoluteFileName=(FileName).fileName
	local RelativeFileName=RelativeTexturesPath+filenameFromPath AbsoluteFileName
	local tmp = (RelativeFileName.count)
	WriteShort file tmp #unsigned
	WriteString file RelativeFileName
	if CopyTextures then
	(
		format "Copy from \"%\" to \"%\"\n" AbsoluteFileName (ExportPath+RelativeFileName)
		copyFile AbsoluteFileName (ExportPath+RelativeFileName)
	)	
)
function GetRelativePath AbsoluteFileName =
(
	local position = findString AbsoluteFileName "Data"
	local RelativePath = substring AbsoluteFileName position -1
	return RelativePath
)
function WriteStaticMeshElement Object3D file SaveInPath =
(
	local relativePathTemp = (SaveInPath+Object3D.name+".mesh")
	local pathTemp = GetRelativePath relativePathTemp
	format "\t<static_mesh name=\"%\" filename=\"%\" />" Object3D.name pathTemp to:file
)
function CreateStaticMeshManager SaveInPath = 
(
	local filename = "StaticMeshManager.xml"
	-- Para crear un fichero de tipo carácter stream
	local file = createfile (SaveInPath+"/"+filename)
	
	if file != undefined then
	(
		local meshes = $*
		-- Para escribir sobre el fichero de tipo carácter stream utilizando la función format
		format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
		format "<static_meshes>\n" to:file
		
		for i = 1 to meshes.count do
		(
			WriteXMLElement meshes[i] file ((GetRelativePath SaveInPath)+"Meshes/")--Si es un directorio diferente se debe agregar la barra al final "/"
		)
		
		format "</static_meshes>\n" to:file
		-- Para cerrar el fichero de tipo carácter stream
		close file
	)
	else
	(
		DisplayWarning "No se ha podido crear el Static Mesh Manager"
	)
)
function WriteXMLElement Object3D file SubDirectory=
(
	format "\t<static_mesh name=\"%\" filename=\"%\" />\n" Object3D.name (SubDirectory+Object3D.name+".mesh") to:file
)

function CreateRenderableObjXML  SaveInPath=
(
	local filename = "RenderableObjects.xml"
	-- Para crear un fichero de tipo carácter stream
	local file = createfile (SaveInPath+"/"+filename)
	
	if file != undefined then
	(
		local meshes = $*
		-- Para escribir sobre el fichero de tipo carácter stream utilizando la función format
		format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
		format "<renderable_objs>\n" to:file
		
		for i = 1 to meshes.count do
		(
			WriteXMLObject meshes[i] file
		)
		
		format "</renderable_objs>\n" to:file
		-- Para cerrar el fichero de tipo carácter streamç
		close file
	)
	else
	(
		DisplayWarning "No se ha podido crear el archivo %" filename
	)
)
function WriteXMLObject Object3D file =
(
	local matrix = Object3D.transform
	local xml = "\t<object "
	
	xml += "name=\"" + Object3D.name + "\" "
	xml += "core=\"" + Object3D.name + "\" "
	xml += "pos=\"" + (matrix.translation.x as string)
	xml += " " + (matrix.translation.y as string)
	xml += " " + (matrix.translation.z as string) + "\" "
	xml += "yaw=\"" + (GetYaw matrix as string) + "\" "
	xml += "pitch=\"" + (GetPitch matrix as string) + "\" "
	xml += "roll=\"" + (GetRoll matrix as string) + "\" "
	
	xml +=" />\n"
	
	format xml to:file
)

fn GetYaw transform =
(
	return (transform as eulerangles).z
)
fn GetPitch transform =
(
	return (transform as eulerangles).x
)
fn GetRoll transform =
(
	return (transform as eulerangles).y
)
