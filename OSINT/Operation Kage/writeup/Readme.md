```
# README:Osint challenge - Operation Kage

## Challenge Breakdown
A high-profile individual has gone missing under mysterious circumstances. Their last known location was near Tokyo Tower, but intelligence suggests they have been relocated 1000-1200 kilometers away. 

### Coded Message
A crucial clue was found in a coded message:
> 冬季スポーツのメダルが輝く場所

Translated, this means:
> "The place where winter sports medals shine."

This strongly hints at a city known for hosting winter sports competitions.

Additionally, another phrase was repeated in the transmission:
> ティックトックティックトックティックトック

This translates to:
> "Tick tock tick tock tick tock"

This suggests a connection to a clock or a famous clock-related landmark.

## Identifying the City
By searching for cities in Japan associated with winter sports, the most prominent result is **Sapporo**, which hosted the **1972 Winter Olympics**. This matches the clue about "winter sports medals."

**Screenshot:**
![Google search results for winter sports cities in Japan](screenshots/1.png)

## Identifying the Location
The repeated mention of "tick tock" suggests a connection to a **clock**. One of the most famous landmarks in Sapporo is the **Sapporo Clock Tower**.

**Screenshot:**
![Sapporo Clock Tower](screenshots/2.png)

### Hidden Clue in Metadata
Examining the metadata of the intercepted image, a phrase was found:
> "I loved handicrafts beside the building of this place."

Additionally, a reference to a "sewing shop" was made. Using **Google Street View** around the **Sapporo Clock Tower**, we can identify a nearby **handicraft store named Mariya** next to a sewing shop.

**Screenshot:**
![image of the building with the given image](screenshots/3.png)

## Solution
The answer follows the format `CSL{nameofbuilding}`.

From our investigation, the building next to the Sapporo Clock Tower is **Mariya Handicraft Store**.

**Final Flag:**
```
CSL{Mariya}
```

## Summary
1. **Identify the city:** Clue about winter sports led to **Sapporo**.
2. **Identify the landmark:** "Tick tock" referred to the **Sapporo Clock Tower**.
3. **Find the adjacent building:** Metadata and additional clues led to **Mariya Handicraft Store**.

Mission Accomplished!

## Supporting Evidence
To validate the findings, include the following screenshots:
- **Google search results** for winter sports cities in Japan.
- **Street View screenshot** of Sapporo Clock Tower and adjacent buildings.
- **Metadata evidence** showing the phrase about handicrafts.
- **Screenshot of the sewing shop and Mariya Handicraft Store** from Google Maps.

**Screenshot:**
![Sewing shop and Mariya Handicraft Store](screenshots/sewing_shop_mariya.png)

These screenshots will serve as proof of the investigation and ensure the accuracy of the findings.
```

