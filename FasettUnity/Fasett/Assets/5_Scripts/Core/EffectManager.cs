using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class EffectManager : MonoBehaviour {
        public void SetEffectValue(string node, float value) {
            Debug.Log(node + " " + value);
        }
    }
}
