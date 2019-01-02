using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Fasett {
    public class Core : MonoBehaviour {
        public static Core Instance { get; private set; }

        [SerializeField] private UserInput _userInput;
        [SerializeField] private EffectManager _effectManager;
        [SerializeField] private NetworkHandler _networkHandler;
        [SerializeField] private StateManager _stateManager;

        public EffectManager EffectManager { get { return _effectManager; } }
        public NetworkHandler NetworkHandler { get { return _networkHandler; } }
        public StateManager StateManager { get { return _stateManager; } }

        protected void Start () {
            Instance = this;
            _userInput.Setup(this);
            _networkHandler.Setup(this);
            _stateManager.Setup(this);
	    }

    }
}
