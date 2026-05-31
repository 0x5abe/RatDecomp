#include "ParticlesAgent_Z.h"

BEGIN_INIT_AGENT_CLASS(ParticlesAgent_Z, Agent_Z)
END_INIT_AGENT_CLASS

ParticlesAgent_Z::ParticlesAgent_Z() {
    EnableFlag(FL_AGENT_PARTICLES);
}