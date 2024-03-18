#include "Actions/Act_Fire.h"

DEFINE_LOG_CATEGORY(ActionLog);

void UAct_Fire::DoAction()
{
	Super::DoAction();

	UE_LOG(ActionLog, Log, TEXT("Fire"));
}
