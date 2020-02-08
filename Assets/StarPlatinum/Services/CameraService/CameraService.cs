﻿using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace StarPlatinum
{
    /// <summary>
    /// 如果没有摄像机，那么实例化一个摄像机并把固定脚本挂上去
    /// 如果有摄像机，没有固定脚本，那么把脚本挂上去
    /// 如果有摄像机，也有固定脚本，那么什么都不做
    /// 如果有多台摄像机
    /// </summary>
	public class CameraService : Singleton<CameraService>
    {
        public enum SceneCameraType
        {
            Fixed,
            Moveable
        }

        [SerializeField]
        private GameObject m_mainCamera;

        [SerializeField]
        private CameraController m_cameraController;
        public CameraController GetCameraController => m_cameraController;

        public CameraService()
        {

            //EventManager.Instance().RegisterCallback((int)LogicType.MainMenuOpen, SetCamera);
            //EventManager.Instance().RegisterCallback((int)LogicType.MainMenuClose, CameraClose);
            //EventManager.Instance().RegisterCallback((int)LogicType.SceneOpen, SetCamera);
            //EventManager.Instance().RegisterCallback((int)LogicType.SceneClose, CameraClose);

            UpdateCurrentCamera();

        }

        public bool UpdateCurrentCamera()
        {
            m_cameraController = null;

            GameObject mainCamera = GetCamera();
            if (mainCamera == null)
            {
                mainCamera = CreateCamera();
                if (mainCamera == null) return false;

            }

            m_cameraController = m_mainCamera.GetComponent<CameraController>();
            if (m_cameraController == null)
            {
                m_cameraController = m_mainCamera.AddComponent<CameraController>();
            }

            return true;
        }

        public void SetTarget(GameObject target)
        {
            if (m_cameraController != null)
            {
                m_cameraController.SetTarget(target);
            }
        }

        private bool CloseAllCamera()
        {
            Camera[] cameras = Camera.allCameras;
            Debug.Log("Camera Length:" + cameras.Length);
            for (int i = 0; i < cameras.Length; i++)
            {
                Debug.Log("Camera" + i + " name: " + cameras[i].name);

                cameras[i].gameObject.SetActive(false);
            }

            m_mainCamera = null;

            return true;
        }

        //public override void SingletonInit ()
        //{

        //      }

        private GameObject GetCamera()
        {

            Camera[] cameras = Camera.allCameras;
            Debug.Log("Camera Length:" + cameras.Length);

            if (Camera.allCamerasCount == 0)
            {
                Debug.Log("This scene doean`t contain a camera!");

                return null;
            }

            if (cameras.Length > 1)
            {
                for (int i = 1; i < cameras.Length; i++)
                {
                    GameObject.Destroy(cameras[i]);
                }
            }

            return cameras[0].gameObject;

        }

        private GameObject CreateCamera()
        {
            GameObject root = GameObject.Find("GameRoot");
            if (root == null) return null;


            camera = new GameObject("Main Camera");
            camera.AddComponent<Camera>();

            //m_cachedCamera = Instantiate (m_cachedCamera);
            camera.transform.SetParent(root.transform);

            return camera;


        }

        //public bool SetCamera (System.Object vars = null)
        //{

        //	m_mainCamera = GetCamera ();
        //	if (m_mainCamera == null) {
        //		CreateCamera (true);

        //	}
        //	return true;
        //}

        private GameObject camera;
    }
}