#pragma once

#include "Enums.h"

namespace Linphone
{
	namespace Core
	{
		ref class LinphoneAddress;
		ref class LinphoneCallLog;
		ref class LinphoneCallStats;
		ref class LinphoneCallParams;
		ref class LinphoneCore;

		/// <summary>
		/// Object representing a call.
		/// Calls are create using LinphoneCore::Invite or passed to the application by the listener LinphoneCoreListener::CallState.
		/// </summary>
		public ref class LinphoneCall sealed
		{
		public:
			LinphoneCallState GetState();
			LinphoneAddress^ GetRemoteAddress();
			CallDirection GetDirection();
			LinphoneCallLog^ GetCallLog();
			LinphoneCallStats^ GetAudioStats();

			/// <summary>
			/// This is usefull for example to know if far end supports video or encryption.
			/// </summary>
			LinphoneCallParams^ GetRemoteParams();
			LinphoneCallParams^ GetCurrentParamsCopy();

			void EnableEchoCancellation(Platform::Boolean enable);
			Platform::Boolean IsEchoCancellationEnabled();
			void EnableEchoLimiter(Platform::Boolean enable);
			Platform::Boolean IsEchoLimiterEnabled();
			int GetDuration();
			
			/// <summary>
			/// Obtain real time quality rating of the call.
			/// Based on local RTP statistics and RTCP feedback, a quality rating is computed and updated during all the duration of the call.
			/// This function returns its value at the time of the function call.
			/// It is expected that the rating is updated at least every 5 seconds or so.
			/// The rating is a floating point number comprised between 0 and 5.
			/// 4-5 = good quality
			/// 3-4 = average quality
			/// 2-3 = poor quality
			/// 1-2 = very poor quality
			/// 0-1 = can't be worse, mostly unusable
			/// </summary>
			/// <returns>
			/// -1 if no quality mesurement is available, for example if no active audio stream exists. Otherwise returns the quality rating.
			/// </returns>
			float GetCurrentQuality();

			/// <summary>
			/// Returns call quality averaged over all the duration of the call.
			/// See GetCurrentQuality for more details about quality mesurement.
			/// </summary>
			float GetAverageQuality();

			/// <summary>
			/// Used by ZRTP encryption mechanism.
			/// </summary>
			/// <returns>
			/// SAS associated to the main stream [voice].
			/// </returns>
			Platform::String^ GetAuthenticationToken();

			/// <summary>
			/// Used by ZRTP mechanism.
			/// SAS can verified manually by the user or automatically using a previously shared secret.
			/// </summary>
			/// <returns>
			/// true if the main stream [voice] SAS was verified.
			/// </returns>
			Platform::Boolean IsAuthenticationTokenVerified();

			/// <summary>
			/// Used by ZRTP mechanism.
			/// </summary>
			/// <param name="verified">true when displayed SAS is correct</param>
			void SetAuthenticationTokenVerified(Platform::Boolean verified);

			Platform::Boolean IsInConference();
			float GetPlayVolume();
			Platform::String^ GetRemoteUserAgent();
			Platform::String^ GetRemoteContact();

			property Platform::Object^ CallContext
            {
                Platform::Object^ get();
				void set(Platform::Object^ cc);
            }

			LinphoneCall(Platform::String^ contact, Platform::String^ number);

		private:
			friend ref class Linphone::Core::LinphoneCore;
			
			Platform::Object^ callContext;

			Platform::String^ contact;
			Platform::String^ number;
		};
	}
}