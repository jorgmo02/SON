using UnityEngine;
using UnityEngine.UI;

public class HandleInput : MonoBehaviour
{
    [SerializeField]
    [Range(0,1)]
    float strength = 1.0f;

    [SerializeField]
    Text strText;

    [SerializeField]
    Slider strSlider;

    [SerializeField]
    [Range(0, 1)]
    float hiHatOpened = 0.0f;

    [SerializeField]
    Text hhOpenText;

    [SerializeField]
    Slider hhOpenSlider;

    [SerializeField]
    HiHat hiHat = null;
    
    [SerializeField]
    PedalHiHat pedalHiHat = null;

    [SerializeField]
    float hihatCloseThreshold = 0.1f;

    bool firstTime = true;

    // Start is called before the first frame update
    void Start()
    {
        updateStrength(strength);
        updateHiHatOpen(hiHatOpened);
        firstTime = false;
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetMouseButtonDown(0))
        {
            Clicked();
        }

        if (Input.GetKeyDown("a"))
        {
            updateHiHatOpen(hiHatOpened - 0.05f);
        }

        if (Input.GetKeyDown("s"))
        {
            updateHiHatOpen(hiHatOpened + 0.05f);
        }

        if (Input.GetKeyDown("z"))
        {
            updateStrength(strength - 0.05f);
        }

        if (Input.GetKeyDown("x"))
        {
            updateStrength(strength + 0.05f);
        }
    }

    void Clicked()
    {
        var ray = Camera.main.ScreenPointToRay(Input.mousePosition);

        //Debug.DrawRay(ray.origin, ray.direction);

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

    public void updateStrength(float st)
    {
        if (strength < 0.0f)
            strength = 0.0f;
        else if (strength > 1.0f)
            strength = 1.0f;

        strength = st;

        if (strText != null)
            strText.text = "Strength: " + strength.ToString("F2");
        else Debug.LogError("Forgot to set the strength text");

        if (strSlider != null)
            strSlider.value = st;
        else Debug.LogError("Forgot to set the strength slider");
    }

    public void updateHiHatOpen(float open)
    {
        Debug.Log("Calling HiHatOpen");

        hiHatOpened = Mathf.Clamp(open, 0f, 1f);

        if (hhOpenText != null)
            hhOpenText.text = "Hi Hat Open: " + hiHatOpened.ToString("F2");
        else Debug.LogError("Forgot to set the hi-hat open text");

        if (hhOpenSlider != null)
            hhOpenSlider.value = hiHatOpened;
        else Debug.LogError("Forgot to set the hi-hat open slider");
        

        if(hiHatOpened < hihatCloseThreshold && !firstTime)
        {
            if (hihatCloseThreshold - hiHatOpened == 0f) hiHatOpened += 0.01f;
            hiHat.CloseHiHat(Mathf.Clamp(strength / (hihatCloseThreshold - hiHatOpened), 0, 1));
            pedalHiHat.ReproduceClose(strength);
        }
    }

    public float getHiHatOpen()
    {
        return hiHatOpened;
    }
}
