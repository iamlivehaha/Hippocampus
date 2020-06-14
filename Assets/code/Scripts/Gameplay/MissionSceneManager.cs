﻿using System.Collections;
using System.Collections.Generic;
using Config.GameRoot;
using StarPlatinum;
using StarPlatinum.Base;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

namespace StarPlatinum.Manager
{
	public class MissionSceneManager : Singleton<MissionSceneManager>
	{
		public string GenerateFolderName (MissionEnum missionEnum)
		{
			return ConfigMission.Instance.Prefix_Mission_Folder + missionEnum.ToString () + "_" + SceneManager.GetActiveScene ().name;
		}

		public string GenerateSceneName (MissionEnum missionEnum)
		{
			if (Application.isPlaying) {
				return ConfigMission.Instance.Prefix_Mission_Scene + missionEnum.ToString () + "_" + GameSceneManager.Instance ().GetCurrentScene ();
			}
			return ConfigMission.Instance.Prefix_Mission_Scene + missionEnum.ToString () + "_" + SceneManager.GetActiveScene ().name;
		}

		//For runtime
		public bool IsMissionSceneExist (MissionEnum mission)
		{
			string missionSceneName = GenerateSceneName (mission);
			if (SceneLookup.IsSceneExistNoMatchCase (missionSceneName)) {
				return true;
			} else {
				Debug.LogWarning ("Request mission scene is not exist: " + mission);
				return false;
			}
		}

		//For editor mode
		public bool IsFileMissionSceneExistInAssets (string folder, string sceneName)
		{
			string pathToScene = GenerateFullSceneFolderPath (folder);
			string [] missionAssets = AssetDatabase.FindAssets (sceneName, new string [] { pathToScene });
			if (missionAssets.Length < 1) {
				Debug.Log ("Cant Find Scene Assets in: " + pathToScene);
				return false;
			}
			if (missionAssets.Length > 1) {
				Debug.LogError ("Scene Assets more than one: " + pathToScene);
				foreach (var sceneFile in missionAssets) {
					Debug.LogError (sceneFile);
				}
				return false;
			}
			return true;
		}


		public string GenerateFullScenePath (string folderName, string sceneName)
		{
			return GenerateFullSceneFolderPath (folderName) + "/" + sceneName + ".unity";
		}

		public string GenerateFullSceneFolderPath (string folderName)
		{
			return ConfigMission.Instance.Path_To_Folder_World + "/" + folderName;
		}

	}
}