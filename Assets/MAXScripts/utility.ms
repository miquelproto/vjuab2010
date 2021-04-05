filein "functions.ms"
utility UABUtility "UAB Utility" width:221 height:373
(
	button SetPathButton "Set Path" pos:[8,8] width:144 height:24
	label pathLabel "Capullo" pos:[8,40] width:184 height:22
	checkbox ExportMeshCheck "Export Mesh" pos:[8,64] width:144 height:18
	checkbox CopyTexturesCheck "Copy Textures" pos:[8,88] width:144 height:18
	GroupBox grp2 "Export" pos:[8,160] width:144 height:144
	button btn3 "Lights" pos:[16,176] width:64 height:24
	button ExportMeshButton "Mesh" pos:[88,176] width:56 height:24
	button ExportSceneButton "Scene" pos:[16,272] width:128 height:24
	button btn6 "Camera" pos:[16,208] width:64 height:24
	button StaticMeshManagerButton "Static Mesh Manager" pos:[16,240] width:128 height:28
	dropdownList LevelList "Levels" pos:[8,112] width:144 height:40
	
	/*FUNCTIONS*/
	function GetDataPath  = 
	(
		if LevelList.selection == 1 then
		(
			return pathLabel.text+"/"
		)
		else 
		(
			return pathLabel.text+"/"+LevelList.items[LevelList.selection]+"/"
		)
	)
	function GetTexturesPath =
	(
		return GetDataPath()+"Textures/"
	)
	function GetMeshesPath =
	(
		return GetDataPath()+"Meshes/"
	)

	/*EVENTS*/
	on UABUtility open do
	(
		local LevelItems = #("","Level1","Level2", "Level3")
		LevelList.items = LevelItems
		--pathLabel.text = "E:/vjuab2010/Run/Test/Data"
		pathLabel.text = "C:/Master/vjuab2010/Run/Test/Data"
		--pathLabel.text = "E:\proy\Run\Test\Data"
	)
	on SetPathButton pressed do
	(
		local data_Path = getSavePath caption:"Data Path" initialDir:pathLabel.text
		if data_Path != undefined then
		(
			pathLabel.text = data_Path
		)
	)
	
	on ExportMeshButton pressed do
	(
		if $!=undefined then
		(
			--DisplayMessage SubDirectory
			local OutputPath=GetDataPath()
			--local out_name="E:/vjuab2010/Run/Test/Data/mi1ermesh.mesh"
			
			local out_name = GetSaveFileName filename:(OutputPath+$.name+".mesh") caption: "Select output file to export file" types:" mesh(*.mesh)|*.mesh|All Files(*.*)|*.*|"
			if out_name!=undefined then
			(
				format "Exportando mallas.\nout_name%\ncheckTextures%\noutputpath%\n"out_name CopyTexturesCheck.checked OutputPath
				ExportMesh $ out_name CopyTexturesCheck.checked "" OutputPath
				--copyFile (OutputPath+$.name+".mesh") (GetMeshesPath+$.name+".mesh")
				--deleteFile (OutputPath+$.name+".mesh")
			)
			else
			(
				DisplayWarning "Nombre de directorio o archivo incorrecto."
			)
		)
		else
		(
			DisplayWarning "Debes seleccionar una malla para realizar esta operacion."
		)
	)
	on StaticMeshManagerButton pressed do
	(
		local ElementsInScene = $*
		local DataPath = GetDataPath()
		local filename = DataPath + "StaticMeshManager.xml"
		local file = createfile filename
		format "<?xml version=\"1.0\" encoding=\"ISO-8859-1\"?>\n" to:file
		format "<static_meshes>\n" to:file
		for i=1 to ElementsInScene.count do
		(
			local element = ElementsInScene[i]
			if ExportMeshCheck.checked then
			(
				local out_name = GetSaveFileName filename:(DataPath+element.name+".mesh") caption: "Select output file to export file" types:" mesh(*.mesh)|*.mesh|All Files(*.*)|*.*|"
				if out_name!=undefined then
				(
					ExportMesh element out_name CopyTexturesCheck.checked "textures" DataPath
					copyFile (DataPath+element.name+".mesh") (GetMeshesPath()+element.name+".mesh")
					deleteFile (DataPath+element.name+".mesh")
				)
			)
			WriteStaticMeshElement element file DataPath
		)
		format "</static_meshes>\n" to:file
		close file
	)
	/*on StaticMeshManagerButton pressed do
	(
		CreateStaticMeshManager GetDataPath ()
	)*/
	on ExportSceneButton pressed do
	(
		local dataPath = GetDataPath()
		
		CreateStaticMeshManager dataPath
		CreateRenderableObjXML dataPath
	)
)
