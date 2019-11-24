using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EncounterController : MonoBehaviour
{
    private enum Mode
    {
        Normal,
        Stealth
    }

    public enum Alignment
    {
        Good,
        Neutral,
        Evil
    }

    public enum Turn
    {
        None,
        Player,
        Opposite
    }

    private Mode currentModePP = Mode.Normal;
    private Mode currentModeOP = Mode.Normal;
    private Turn currentTurn = Turn.None;
    private int numberTurn = 0;

    public class Character
    {
        public string Name;

        public Alignment Alignment;

        public int Level;

        public int Might;
        public int Dexterity;
        public int Intellect;

        public int HP;
        public int XP;
        public int Armor;

        public int Athletics;
        public int MeleeWeapons;
        public int RangeWeapons;

        public int Stealth;
        public int Thievery;
        public int Acrobatics;

        public int Perception;
        public int Negotiation;
        public int Technology;

        public int Initiative;
    }

    private List<Character> playerParty = new List<Character>();
    private List<Character> oppositeParty = new List<Character>();

    // Start is called before the first frame update
    private void Start()
    {
        CreateStartingParty();

        ShowHelp();
    }

    private void CreateStartingParty()
    {
        playerParty.Add(new Character());

        playerParty[0].Name = "Saffron";

        playerParty[0].Alignment = Alignment.Neutral;

        playerParty[0].Level = 1;

        playerParty[0].Might = 4;
        playerParty[0].Dexterity = 2;
        playerParty[0].Intellect = 0;

        playerParty[0].Athletics = 1;
        playerParty[0].MeleeWeapons = 2;
        playerParty[0].RangeWeapons = 1;

        playerParty[0].Stealth = 1;
        playerParty[0].Thievery = 1;
        playerParty[0].Acrobatics = 0;

        playerParty[0].Perception = 0;
        playerParty[0].Negotiation = 0;
        playerParty[0].Technology = 0;
    }

    private Character CreateRandomCharacter()
    {
        Character character = new Character();

        character.Name = System.Guid.NewGuid().ToString();

        character.Level = Random.Range(Mathf.Clamp(playerParty[0].Level - 1, 0, 99),
                                        Mathf.Clamp(playerParty[0].Level + 3, 0, 99));

        // Abilities.

        int pool = character.Level + 5;

        character.Might = Random.Range(0, pool + 1);
        pool -= character.Might;

        character.Dexterity = Random.Range(0, pool + 1);
        pool -= character.Dexterity;

        character.Intellect = Random.Range(0, pool + 1);
        pool -= character.Intellect;

        // Skills.

        pool = character.Might;
        character.Athletics = Random.Range(0, pool + 1);
        pool -= character.Athletics;

        character.MeleeWeapons = Random.Range(0, pool + 1);
        pool -= character.MeleeWeapons;

        character.RangeWeapons = Random.Range(0, pool + 1);
        pool -= character.MeleeWeapons;

        pool = character.Dexterity;
        character.Stealth = Random.Range(0, pool + 1);
        pool -= character.Stealth;

        character.Thievery = Random.Range(0, pool + 1);
        pool -= character.Thievery;

        character.Acrobatics = Random.Range(0, pool + 1);
        pool -= character.Acrobatics;

        pool = character.Intellect;
        character.Perception = Random.Range(0, pool + 1);
        pool -= character.Perception;

        character.Negotiation = Random.Range(0, pool + 1);
        pool -= character.Negotiation;

        character.Technology = Random.Range(0, pool + 1);
        pool -= character.Technology;

        return character;
    }

    // Update is called once per frame
    private void Update()
    {
        if (Input.GetKeyDown(KeyCode.H))
        {
            ShowHelp();
        }

        if (currentTurn != Turn.None)
        {
            RunEncounter();
        }
        else
        {
            RunExplotarion();
        }
    }

    private void RunExplotarion()
    {
        if (Input.GetKeyDown(KeyCode.Keypad1))
        {
            SetModePP(Mode.Normal);
        }
        else if (Input.GetKeyDown(KeyCode.Keypad2))
        {
            SetModePP(Mode.Stealth);
        }
        else if (Input.GetKeyDown(KeyCode.W))
        {
            Debug.Log("Advancing...");

            CalcEncounter();
        }
    }

    private void SetModePP(Mode mode)
    {
        Debug.Log("Set Mode PP: " + mode);

        currentModePP = mode;
    }

    private void SetModeOP(Mode mode)
    {
        Debug.Log("Set Mode OP: " + mode);

        currentModeOP = mode;
    }

    private void ShowHelp()
    {
        Debug.Log("Press 1 to set Normal Mode (Walking speed, easier to fall into encounters and traps)");
        Debug.Log("Press 2 to set Stealth Mode (Slow speed, easier to detect encounters and traps)");
        Debug.Log("Press H to show help");
        Debug.Log("Press W to advance");
    }

    private void CalcEncounter()
    {
        // Keep it easy to test, create encounters half of the time.
        if (Random.Range(0, 100) > 50)
        {
            CreateEncounter();
        }
    }

    private bool IsHostile(Alignment source, Alignment target)
    {
        if (source == Alignment.Evil)
        {
            return true;
        }
        else if (source == Alignment.Good && target == Alignment.Evil)
        {
            return true;
        }

        return false;
    }

    private int fightTotal = 0;
    private int stealthTotal = 0;
    private int athleticsTotal = 0;
    private int negotiationTotal = 0;

    private Alignment alignmentOP = Alignment.Neutral;

    private void CreateEncounter()
    {
        // Reset.
        numberTurn = 0;
        oppositeParty.Clear();

        // Create Opposite Party.
        int count = Random.Range(1, 3 + 1);
        for (int i = 0; i < count; i++)
        {
            oppositeParty.Add(CreateRandomCharacter());
        }

        // Decide Alignment.
        alignmentOP = (Alignment)Random.Range(0, 3);

        Debug.Log("OP Alignment: " + alignmentOP);
        Debug.Log("OP count: " + count);

        // Set mode based on the overall best skill of the party.

        for (int i = 0; i < oppositeParty.Count; i++)
        {
            fightTotal += oppositeParty[i].MeleeWeapons > oppositeParty[i].RangeWeapons ? +oppositeParty[i].MeleeWeapons : oppositeParty[i].MeleeWeapons;

            stealthTotal += oppositeParty[i].Stealth;

            athleticsTotal += oppositeParty[i].Athletics;

            negotiationTotal += oppositeParty[i].Negotiation;
        }

        if (stealthTotal > fightTotal)
        {
            SetModeOP(Mode.Stealth);
        }
        else
        {
            SetModeOP(Mode.Normal);
        }

        // Check who goes first.

        int initiativeOP = 0;
        int initiativePP = 0;

        for (int i = 0; i < oppositeParty.Count; i++)
        {
            switch (currentModeOP)
            {
                case Mode.Normal:
                    oppositeParty[i].Initiative = Random.Range(1, 20 + 1) + oppositeParty[i].Perception;
                    break;

                case Mode.Stealth:
                    oppositeParty[i].Initiative = Random.Range(1, 20 + 1) + oppositeParty[i].Stealth;
                    break;
            }

            // Get the worst result (the worst member is always a burden).
            if (i == 0 || oppositeParty[i].Initiative < initiativeOP)
            {
                initiativeOP = oppositeParty[i].Initiative;
            }
        }

        for (int i = 0; i < playerParty.Count; i++)
        {
            switch (currentModePP)
            {
                case Mode.Normal:
                    playerParty[i].Initiative = Random.Range(1, 20 + 1) + playerParty[i].Perception;
                    break;

                case Mode.Stealth:
                    playerParty[i].Initiative = Random.Range(1, 20 + 1) + playerParty[i].Stealth;
                    break;
            }

            // Get the worst result (the worst member is always a burden).
            if (i == 0 || playerParty[i].Initiative < initiativePP)
            {
                initiativePP = playerParty[i].Initiative;
            }
        }

        Debug.Log("initiativeOP: " + initiativeOP);
        Debug.Log("initiativePP: " + initiativePP);

        // Player Party goes first.
        if (initiativePP >= initiativeOP)
        {
            currentTurn = Turn.Player;

            for (int i = 0; i < oppositeParty.Count; i++)
            {
                Debug.Log("A creature appears, Might " + oppositeParty[i].Might + " Dexterity " + oppositeParty[i].Dexterity + " Intellect " + oppositeParty[i].Intellect);
            }

            Debug.Log("(F)ight, (C)hat, (L)eave");
        }
        // Opposite Party goes first.
        else
        {
            currentTurn = Turn.Opposite;
        }
    }

    private void RunEncounter()
    {
        if (currentTurn == Turn.Player)
        {
            if (opDemanded)
            {
                if (Input.GetKeyDown(KeyCode.A))
                {
                    AcceptDemand();
                }
                else if (Input.GetKeyDown(KeyCode.R))
                {
                    RefuseDemand();
                }
            }
            else if (opAsked)
            {
                if (Input.GetKeyDown(KeyCode.A))
                {
                    Debug.Log("Player accepted.");

                    NextTurn();
                }
                else if (Input.GetKeyDown(KeyCode.R))
                {
                    Debug.Log("Player refused.");

                    NextTurn();
                }
            }
            else
            {
                if (Input.GetKeyDown(KeyCode.L))
                {
                    if (numberTurn == 0)
                    {
                        Debug.Log("Your party leaves.");
                        EndEncounter();
                    }
                    else
                    {
                        if (CouldLeave(playerParty, oppositeParty, playerParty[0].Alignment, alignmentOP))
                        {
                            Debug.Log("Your party leaves.");
                            EndEncounter();
                        }
                        else
                        {
                            Debug.Log("You party can't leave!");
                            NextTurn();
                        }
                    }
                }
            }
        }
        else if (currentTurn == Turn.Opposite)
        {
            OppositeDecideAction();
        }
    }

    private void NextTurn()
    {
        Debug.Log("Next");

        numberTurn++;

        if (currentTurn == Turn.Opposite)
        {
            currentTurn = Turn.Player;

            if (opDemanded || opAsked)
            {
                Debug.Log("(A)ccept, (R)efuse");
            }
            else
            {
                Debug.Log("(F)ight, (C)hat, (L)eave");
            }
        }
        else
        {
            currentTurn = Turn.Opposite;
        }
    }

    private void EndEncounter()
    {
        currentTurn = Turn.None;

        ShowHelp();
    }

    private bool CouldLeave(List<Character> source, List<Character> target, Alignment sourceAl, Alignment targetAl)
    {
        if (IsHostile(targetAl, sourceAl))
        {
            int rollSource = 0;
            int rollTarget = 0;

            for (int i = 0; i < source.Count; i++)
            {
                int roll = Random.Range(1, 20 + 1) + source[i].Athletics;

                if (roll > rollSource)
                {
                    rollSource = roll;
                }
            }

            for (int i = 0; i < target.Count; i++)
            {
                int roll = Random.Range(1, 20 + 1) + target[i].Athletics;

                if (i == 0 || rollTarget > roll)
                {
                    rollTarget = roll;
                }
            }

            return rollTarget >= rollSource;
        }

        return true;
    }

    private void OppositeDecideAction()
    {
        // If the OP is hostile...
        if (IsHostile(alignmentOP, playerParty[0].Alignment))
        {
            if (fightTotal > negotiationTotal)
            {
                OppositeActionFight();
            }
            else
            {
                OppositeActionNegotiate();
            }
        }
        // OP not hostile
        else
        {
            // If the PP is hostile...
            if (IsHostile(playerParty[0].Alignment, alignmentOP))
            {
                if (athleticsTotal > fightTotal || (numberTurn == 0 && currentModeOP == Mode.Stealth))
                {
                    OppositeActionEvade();
                }
            }
            else
            {
                OppositeActionNegotiate();
            }
        }
    }

    private void OppositeActionFight()
    {
        Debug.Log("OP Fight");
        NextTurn();
    }

    private bool opDemanded = false;
    private bool opAsked = false;

    private void OppositeActionNegotiate()
    {
        // If the OP is hostile DEMAND.
        if (IsHostile(alignmentOP, playerParty[0].Alignment))
        {
            opDemanded = true;
            Debug.Log("OP Demand");
        }
        // If the OP is friendly ASK.
        else
        {
            opAsked = true;
            Debug.Log("OP Ask");
        }

        NextTurn();
    }

    private void OppositeActionEvade()
    {
        if (numberTurn == 0)
        {
            Debug.Log("OP leaves.");
            EndEncounter();
        }
        else
        {
            if (CouldLeave(oppositeParty, playerParty, alignmentOP, playerParty[0].Alignment))
            {
                Debug.Log("OP leaves.");
                EndEncounter();
            }
            else
            {
                Debug.Log("OP tries to leave, but you stop them!");
                NextTurn();
            }
        }
    }

    private void AcceptDemand()
    {
    }

    private void RefuseDemand()
    {
    }
}
