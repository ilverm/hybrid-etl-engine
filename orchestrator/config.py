from pydantic_settings import BaseSettings, SettingsConfigDict

class Settings(BaseSettings):
    DB_HOST: str = ""
    DB_PORT: int = 0
    DB_NAME: str = ""
    DB_USER: str = ""
    DB_PASSWORD: str = ""

    @property
    def connection_string(self):
        return f"postgresql://{self.DB_USER}:{self.DB_PASSWORD}@{self.DB_HOST}:{self.DB_PORT}/{self.DB_NAME}"

    model_config = SettingsConfigDict(env_file=".env")

settings = Settings()

connection_string = settings.connection_string