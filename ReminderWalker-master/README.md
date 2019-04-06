# ReminderWalker
This repository contains the data acquisition/control and analysis software for an interactive mobility assistance device (walker), colloquially referred to as the "Reminder Walker", which audibly/visually queues its owner to use their walker when they begin to walk away from it.  

## Project Overview
The project is at the intersection of gerontechnology and smart-health.  A standard walker is equipped with various sensors and audio/visual IO components connected to a microcontroller (1st gen: Arduino) that processes the incoming sensor data, determines when the user stands, and reminds the person (via audio/visual queues) to use their walker if their subsequent movement indicates they are walking away without it.  

## Data Analysis
The acquired data relevant to determining short-term/long-term walker usage patterns and trends is logged and transmitted to a secondary (potentially off-site) location for analysis.  Such datalogging and analysis can be used to:

* record biosensor and mobility/activity information that physicians/family can use to help assess and monitor user health
* identify short-term changes in usage that could indicate a sudden/sharp decline in health that would necessitate an immediate physician, family, or emergency service visit   
* identify long-term changes in usage that could indicate gradual improvements/declines in health and help physicians/family set and adjust how often they visit

## Home Operation
Each walker system will include a home docking station for recharging its LiPO batteries and collecting/storing/analyzing data.  The 2nd+ gen system will include additional health/vitals sensors and incorporate IoT connectivity and devices/accessories.  This will provide more extensive/detailed health indicators and improve communication (data and dialogue) between the user and their physician/family.  

## Mobile and Community Operation
The IoT devices/accessories will also provide many of the capabilities of the home base station, allowing these to largely be maintained outside the home.  This necessitates the ability to have more than one such device operating in the same area where they must be independently operable, particularly in environments such as retirement and assisted living communities.  Additional optional features for such environments include the ability to set spatial boundaries on user movement and establish restricted areas such that the interested party receives a notification if the user crosses into a disallowed area.  This is particularly helpful for those with dementia and other cognitive deficits that often get lost when they wander outside familiar areas.   
