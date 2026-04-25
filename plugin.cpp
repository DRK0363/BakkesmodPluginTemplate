#include "pch.h"
#include "plugin.h"

BAKKESMOD_PLUGIN(BakkesPluginTemplate, "Steam Profile Pictures", "1.0", PERMISSION_ALL)

void BakkesPluginTemplate::onLoad() {
    // Her türlü oyun modunda (3v3, Rumble vb.) skor tablosu açıldığında tetiklenir
    gameWrapper->HookEvent("Function RocketLeague.GFxShell_TA.ShowScoreboard", [this](std::string eventName) {
        if (!gameWrapper->IsInGame()) return;

        auto players = gameWrapper->GetGameEventAsServer().GetPRs();
        for (auto pr : players) {
            if (pr.isNull()) continue;
            
            UniqueIDWrapper uid = pr.GetUniqueIdWrapper();
            // Sadece Steam ID'sine sahip oyuncuları yakalar
            if (uid.GetUID() != 0 && uid.GetIdString().length() > 10) {
                // Burada Steam API üzerinden fotoğraf çekme işlemi başlar
                LOG("Steam ID bulundu: " + uid.GetIdString());
            }
        }
    });
}

void BakkesPluginTemplate::onUnload() {}
