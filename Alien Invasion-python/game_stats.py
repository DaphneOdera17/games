class GameStats:
    """跟踪游戏的统计信息"""

    def __init__(self, ai_game):
        """初始化"""
        self.settings = ai_game.settings
        self.reset_stats()

        # 游戏刚启动时处于活跃状态
        self.game_active = True

    def reset_stats(self):
        """初始化在游戏运行期间可能变化的统计信息"""
        self.ships_left = self.settings.ship_limit