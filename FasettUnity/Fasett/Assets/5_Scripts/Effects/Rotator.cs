using UnityEngine;
using System.Collections;

public class Rotator : MonoBehaviour {
	public Vector3 Rotation {get {return m_rotation;}}

	[SerializeField] private Vector3 m_rotation;

	// Update is called once per frame
	void Update () 	{
		transform.Rotate(m_rotation * Time.deltaTime);
	}

	public void SetRotation(Vector3 rotation)	{
		m_rotation = rotation;
	}
}
