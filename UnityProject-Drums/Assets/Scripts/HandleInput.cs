using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HandleInput : MonoBehaviour
{
    [SerializeField]
    [Range(0,1)]
    float strength = 1.0f;

    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Clicked();
        }

        if (Input.GetKeyDown("-"))
        {
            strength -= .5f;
            if (strength < 0.0f)
                strength = 0.0f;
        }

        if (Input.GetKeyDown("+"))
        {
            strength -= .5f;
            if (strength > 1.0f)
                strength = 1.0f;
        }
    }

    void Clicked()
    {
        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        RaycastHit hit;

        if (Physics.Raycast(ray, out hit))
        {
            // si soy un instrumento
            AbstractInstrument instrument = hit.collider.gameObject.GetComponent<AbstractInstrument>();
            if (instrument != null) {
                // lo llamo y que el solo haga su magia
                instrument.Reproduce(hit.point, strength);   
            }
        }
    }
}
