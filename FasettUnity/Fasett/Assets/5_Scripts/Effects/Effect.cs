using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public abstract class Effect : MonoBehaviour {
        [SerializeField] protected string _effectName;
        public string Name { get { return _effectName; } }

        public abstract void SetValue(float value);
    }
}
